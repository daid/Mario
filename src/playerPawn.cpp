#include "playerPawn.h"
#include "inputController.h"
#include "fireball.h"
#include "brickPiece.h"
#include "main.h"
#include "enemy/enemy.h"

#include <sp2/engine.h>
#include <sp2/random.h>
#include <sp2/scene/camera.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/tilemap.h>
#include <sp2/collision/2d/box.h>
#include <sp2/audio/sound.h>
#include <sp2/graphics/spriteAnimation.h>

//Convert mario subpixel acceleration from subpixels at 60 ups to velocity delta at 30 ups.
// http://photobucket.com/gallery/user/jdaster64/media/bWVkaWFJZDo5MzAyOTA2Nw==/?ref=
static constexpr double subpixelToAcceleration(int subpixel)
{
    return (double(subpixel) / double(0x10000)) * 60.0 * 60.0 / sp::Engine::fixed_update_frequency;
}
//Convert mario subpixel speed from subpixels at 60 ups to units per second.
// http://photobucket.com/gallery/user/jdaster64/media/bWVkaWFJZDo5MzAyOTA2Nw==/?ref=
static constexpr double subpixelToSpeed(int subpixel)
{
    return (double(subpixel) / double(0x10000)) * 60.0;
}

sp::PList<PlayerPawn> PlayerPawn::all;

PlayerPawn::PlayerPawn(sp::P<sp::Node> parent, InputController& controller, sp::string animation_name)
: sp::Node(parent), controller(controller), animation_name(animation_name)
{
    setupCollisionShape();
    
    state = State::Falling;
    
    animation = sp::SpriteAnimation::load(animation_name);
    
    all.add(this);
}

void PlayerPawn::onUpdate(float delta)
{
    if (invincibility_time > 0.0)
    {
        invincibility_time -= delta;
        if (std::fmod(invincibility_time, 0.2) < 0.1)
            render_data.color.a = 0;
        else
            render_data.color.a = 255;
    }
    else
    {
        render_data.color.a = 255;
    }
    
    if (controller.right.get())
        left = false;
    if (controller.left.get())
        left = true;
    animation->setFlags(left ? sp::SpriteAnimation::FlipFlag : 0);
    switch(state)
    {
    case State::Death:
        animation->play("Death");
        break;
    case State::Finish:
        switch(finish_state)
        {
        case FinishSubState::GlidingDownPole:
            animation->play(animation_prefix + "Climb", 0);
            break;
        case FinishSubState::Walking:
            animation->play(animation_prefix + "Walk");
            break;
        case FinishSubState::Stopped:
            animation->play(animation_prefix + "Stand");
            break;
        }
        left = false;
        animation->setFlags(0);
        break;
    case State::Swimming:
        animation->play(animation_prefix + "Swim");
        break;
    case State::EnterPipe:
        if (PipeEntrance::active_entrance && std::abs(PipeEntrance::active_entrance->getPosition2D().x - getPosition2D().x) > 0.1)
            animation->play(animation_prefix + "Walk");
        else
            animation->play(animation_prefix + "Stand");
        break;
    case State::Walking:
        if (skidding)
            animation->play(animation_prefix + "Skid");
        else if (controller.left.get() || controller.right.get())
            animation->play(animation_prefix + "Walk");
        else
            animation->play(animation_prefix + "Stand");
        break;
    case State::Falling:
    case State::Jumping:
        animation->play(animation_prefix + "Jump");
        break;
    }
    
    if (controller.running.getDown() && state != State::Death && state != State::Finish && state != State::EnterPipe && animation_prefix == "Fire")
    {
        Fireball* fireball = new Fireball(getParent(), left);
        sp::audio::Sound::play("sfx/smb_fireball.wav");
        if (left)
            fireball->setPosition(getPosition2D() + sp::Vector2d(-0.2, 0));
        else
            fireball->setPosition(getPosition2D() + sp::Vector2d(0.2, 0));
    }
}

void PlayerPawn::onFixedUpdate()
{
    sp::Vector2d velocity = getLinearVelocity2D();

    if (state == State::Death)
    {
        setPosition(getPosition2D() + sp::Vector2d(0, death_velocity));
        death_velocity -= 0.5 * sp::Engine::fixed_update_delta;
        if (getPosition2D().y < -2.0)
            delete this;
        return;
    }
    if (state == State::Finish)
    {
        switch(finish_state)
        {
        case FinishSubState::GlidingDownPole:
            velocity.y = -subpixelToSpeed(0x2000);
            setLinearVelocity(velocity);
            break;
        case FinishSubState::Walking:
            velocity.y -= subpixelToAcceleration(0x700);
            velocity.x = subpixelToSpeed(0x1900);
            setLinearVelocity(velocity);
            if (getPosition2D().x >= finish_final_x)
            {
                finish_state = FinishSubState::Stopped;
                removeCollisionShape();
            }
            break;
        case FinishSubState::Stopped:
            break;
        }
        return;
    }
    if (state == State::EnterPipe)
    {
        if (!PipeEntrance::active_entrance)
        {
            setupCollisionShape();
            render_data.order = 0;
            state = State::Falling;
            return;
        }
        sp::Vector2d target = PipeEntrance::active_entrance->getPosition2D();
        if (getPosition2D().x <= target.x - 0.1)
            setPosition(getPosition2D() + sp::Vector2d(subpixelToSpeed(0x0300) * sp::Engine::fixed_update_delta, 0));
        else if (getPosition2D().x >= target.x + 0.1)
            setPosition(getPosition2D() - sp::Vector2d(subpixelToSpeed(0x0300) * sp::Engine::fixed_update_delta, 0));
        else
            setPosition(target);
        return;
    }

    if (state == State::Swimming)
    {
        velocity.y -= subpixelToAcceleration(0x0a0);
    }else{
        if (jump_start_velocity_x > subpixelToSpeed(0x2500))
            velocity.y -= subpixelToAcceleration(0x900);
        else if (jump_start_velocity_x > subpixelToSpeed(0x1000))
            velocity.y -= subpixelToAcceleration(0x600);
        else
            velocity.y -= subpixelToAcceleration(0x700);
    }
    
    if (state == State::Jumping)
    {
        //If the jump button is still being pressed while moving up, remove a big chunk of the gravity.
        //This allows controlled jump height.
        if (velocity.y > 0 && controller.jump.get())
        {
            if (jump_start_velocity_x > subpixelToSpeed(0x2500))
                velocity.y += subpixelToAcceleration(0x900 - 0x280);
            else if (jump_start_velocity_x > subpixelToSpeed(0x1000))
                velocity.y += subpixelToAcceleration(0x600 - 0x1E0);
            else
                velocity.y += subpixelToAcceleration(0x700 - 0x200);
        }
        else
        {
            state = State::Falling;
        }
    }
    if (state == State::Swimming)
    {
        if (velocity.y > 0 && controller.jump.get())
            velocity.y += subpixelToAcceleration(0x0a0 - 0x0d0);
    }

    //Limit falling velocity.
    if (velocity.y < -subpixelToSpeed(0x4000))
        velocity.y = -subpixelToSpeed(0x4000);
    
    float x_request = controller.right.getValue() - controller.left.getValue();
    bool flip = false;
    if (velocity.x < 0)
    {
        flip = true;
        velocity.x = -velocity.x;
        x_request = -x_request;
    }

    if (state == State::Walking)
    {
        if (x_request > 0)
        {
            skidding = false;
            if (velocity.x < subpixelToSpeed(0x0130))
                velocity.x = subpixelToSpeed(0x0130);
            if (controller.running.get() && !isInWater())
            {
                velocity.x += subpixelToAcceleration(0x00E4);
                if (velocity.x > subpixelToSpeed(0x2900))
                    velocity.x = subpixelToSpeed(0x2900);
            }else{
                velocity.x += subpixelToAcceleration(0x0098);
                if (velocity.x > subpixelToSpeed(0x1900))
                    velocity.x = subpixelToSpeed(0x1900);
            }
        }
        else if (x_request < 0)
        {
            if (velocity.x < subpixelToSpeed(0x0900))
            {
                velocity.x = -subpixelToSpeed(0x0130);
            }
            else
            {
                skidding = true;
                velocity.x -= subpixelToAcceleration(0x01a0);
            }
        }
        else
        {
            if (velocity.x > subpixelToSpeed(0x0130) && !isInWater())
            {
                if (skidding)
                    velocity.x -= subpixelToAcceleration(0x01a0);
                else
                    velocity.x -= subpixelToAcceleration(0x00D0);
                if (velocity.x < 0)
                    velocity.x = 0;
            }
            else
            {
                velocity.x = 0;
                skidding = false;
            }
        }
        
        if (controller.jump.getDown())
        {
            if (isInWater())
            {
                sp::audio::Sound::play("sfx/smb_stomp.wav");
                state = State::Swimming;
                jump_start_velocity_x = 0;
                velocity.y = subpixelToSpeed(0x1800);
            }
            else
            {
                state = State::Jumping;
                jump_start_velocity_x = std::abs(velocity.x);
                if (jump_start_velocity_x > subpixelToSpeed(0x2500))
                    velocity.y = subpixelToSpeed(0x5000);
                else
                    velocity.y = subpixelToSpeed(0x4000);
                if (animation_prefix == "")
                    sp::audio::Sound::play("sfx/smb_jump-small.wav");
                else
                    sp::audio::Sound::play("sfx/smb_jump-super.wav");
            }
        }
    }
    else
    {
        //Air control
        if (x_request > 0)
        {
            if (velocity.x < subpixelToSpeed(0x0130))
                velocity.x = subpixelToSpeed(0x0130);
            if (velocity.x > subpixelToSpeed(0x1900))
                velocity.x += subpixelToAcceleration(0x00e4);
            else
                velocity.x += subpixelToAcceleration(0x0098);
        }
        if (x_request < 0)
        {
            if (velocity.x < subpixelToSpeed(0x0130))
                velocity.x = 0.0;
            if (velocity.x > subpixelToSpeed(0x1900))
                velocity.x -= subpixelToAcceleration(0x00e4);
            else if (jump_start_velocity_x > subpixelToSpeed(0x1d00))
                velocity.x -= subpixelToAcceleration(0x00d0);
            else
                velocity.x -= subpixelToAcceleration(0x0098);
        }
        if (velocity.x > subpixelToSpeed(0x1900) && jump_start_velocity_x <= subpixelToSpeed(0x1900))
            velocity.x = subpixelToSpeed(0x1900);
        if (velocity.x > subpixelToSpeed(0x2900))
            velocity.x = subpixelToSpeed(0x2900);

        if (controller.jump.getDown() && state == State::Swimming)
        {
            sp::audio::Sound::play("sfx/smb_stomp.wav");
            velocity.y = subpixelToSpeed(0x1800);
        }
    }
    if (flip)
        velocity.x = -velocity.x;

    //Change to falling state if we are moving down.
    if (velocity.y < -subpixelToSpeed(0x1000) && state == State::Walking)
    {
        if (isInWater())
            state = State::Swimming;
        else
            state = State::Falling;
    }
    if (isInWater() && state == State::Falling)
    {
        state = State::Swimming;
        velocity.y /= 5;
    }
    if (!isInWater() && state == State::Swimming)
    {
        if (velocity.y > 0)
        {
            state = State::Jumping;
            velocity.y = subpixelToSpeed(0x4000);
        }
        else
            state = State::Falling;
    }
    
    sp::P<sp::Camera> camera = getScene()->getCamera();
    double push_back_x = camera->getPosition2D().x - 7.5;
    double push_front_x = camera->getPosition2D().x + 7.5;
    double min_allowed_x = push_back_x - 1.5;
    sp::Vector2d position = getPosition2D();
    if (push_back_x > position.x)
        velocity.x = std::max(subpixelToSpeed(0x4000) * (push_back_x - position.x), velocity.x);
    if (push_front_x < position.x)
        velocity.x = std::min(subpixelToSpeed(0x4000) * (push_front_x - position.x), velocity.x);
    if (min_allowed_x > position.x || position.y < -1.0)
    {
        die();
    }
    
    setLinearVelocity(velocity);
}

void PlayerPawn::onCollision(sp::CollisionInfo& info)
{
    if (state == State::Death)
        return;
    if (state == State::EnterPipe)
        return;
    if (state == State::Finish)
    {
        if (finish_state == FinishSubState::GlidingDownPole)
        {
            if (info.normal.y < -0.7 && getLinearVelocity2D().y <= info.other->getLinearVelocity2D().y)
            {
                if (!sp::P<PlayerPawn>(info.other)) //Glided to the ground.
                    finish_state = FinishSubState::Walking;
            }
        }
        return;
    }
    if (bool(info.other) && info.other->isSolid())
    {
        if (invincibility_time > 0 && invincibility_auto_kill)
        {
            sp::P<Enemy> enemy = info.other;
            if (enemy)
            {
                enemy->kill();
                return;
            }
        }
        if (info.normal.y < -0.7 && getLinearVelocity2D().y <= info.other->getLinearVelocity2D().y)
        {
            if (sp::P<PlayerPawn>(info.other))
            {
                //Jumped on top of another player. Bounce off.
                didHeadBump();
            }
            else
            {
                //Hit the ground.
                state = State::Walking;
                //Note: Setting the start velocity is not normal Mario behaviour. However, without this you get inconsistant walking off platform behaviour.
                jump_start_velocity_x = 0;
            }
        }
        if (info.normal.y > 0.7 && getLinearVelocity2D().y >= info.other->getLinearVelocity2D().y)
        {
            //Hit your head.
            if (state == State::Jumping)
                state = State::Falling;
            if (animation_prefix != "")
            {
                sp::P<sp::Tilemap> tilemap = info.other;
                if (tilemap)
                {
                    int tile_index = tilemap->getTileIndex(info.position.x, info.position.y + 0.5);
                    if (tile_index == 1 || tile_index == 19 || tile_index == 99)
                    {
                        int x = info.position.x;
                        int y = info.position.y + 0.5;
                        tilemap->setTile(x, y, -1);
                        sp::string animation = "Brick";
                        if (tile_index == 19) animation = "BrickUnderground";
                        if (tile_index == 99) animation = "BrickCastle";
                        (new BrickPiece(getParent(), x + 0.25, y + 0.25, true, false))->animation->play(animation);
                        (new BrickPiece(getParent(), x + 0.75, y + 0.25, false, false))->animation->play(animation);
                        (new BrickPiece(getParent(), x + 0.25, y + 0.75, true, true))->animation->play(animation);
                        (new BrickPiece(getParent(), x + 0.75, y + 0.75, false, true))->animation->play(animation);
                        sp::audio::Sound::play("sfx/smb_breakblock.wav");
                        return;
                    }
                }
            }
            sp::audio::Sound::play("sfx/smb_bump.wav");
        }
    }
}

void PlayerPawn::didHeadBump()
{
    if (state == State::Death || state == State::Finish || state == State::EnterPipe) return;

    sp::audio::Sound::play("sfx/smb_stomp.wav");
    setLinearVelocity(sp::Vector2d(getLinearVelocity2D().x, subpixelToSpeed(0x4000)));
    if (isInWater())
        state = State::Swimming;
    else
        state = State::Jumping;
}

void PlayerPawn::trampolineFire()
{
    if (state == State::Death || state == State::Finish || state == State::EnterPipe) return;

    setLinearVelocity(sp::Vector2d(getLinearVelocity2D().x, subpixelToSpeed(0x7000)));
    state = State::Jumping;
    jump_start_velocity_x = 0;
}

bool PlayerPawn::takeDamage()
{
    if (invincibility_time > 0.0)
        return false;
    if (state == State::Death)
        return false;
    setInvincibilityTime(1.0, false);
    if (animation_prefix != "")
    {
        animation_prefix = "";
        sp::audio::Sound::play("sfx/smb_pipe.wav");

        setupCollisionShape();
        setPosition(getPosition2D() + sp::Vector2d(0,-0.5));
    }
    else
    {
#ifndef DEBUG
        die();
#endif
    }
    return true;
}

void PlayerPawn::gotFlagpole(double x)
{
    if (state == State::Death || state == State::Finish || state == State::EnterPipe)
        return;
    sp::audio::Sound::play("sfx/smb_flagpole.wav");
    setPosition(sp::Vector2d(x - 0.3, getPosition2D().y));
    setLinearVelocity(sp::Vector2d(0, 0));
    state = State::Finish;
    finish_state = FinishSubState::GlidingDownPole;
    finish_final_x = x + 6 + sp::random(-0.5, 0.5);
}

void PlayerPawn::finish()
{
    if (state == State::Death || state == State::Finish || state == State::EnterPipe)
        return;
    state = State::Finish;
    finish_state = FinishSubState::Walking;
    finish_final_x = getPosition2D().x + 1.0 + sp::random(-0.5, 0.5);
}

bool PlayerPawn::upgrade()
{
    if (animation_prefix == "")
    {
        animation_prefix = "Large";
        setupCollisionShape();
        sp::audio::Sound::play("sfx/smb_powerup.wav");
        return true;
    }
    if (animation_prefix == "Large")
    {
        sp::audio::Sound::play("sfx/smb_powerup.wav");
        animation_prefix = "Fire";
        return true;
    }
    return false;
}

int PlayerPawn::getUpgradeLevel()
{
    if (animation_prefix == "Large")
        return 1;
    if (animation_prefix == "Fire")
        return 1;
    return 0;
}

bool PlayerPawn::setInvincibilityTime(float time, bool auto_kill)
{
    if (time > invincibility_time)
    {
        invincibility_time = time;
        invincibility_auto_kill = auto_kill;
        return true;
    }
    return false;
}

bool PlayerPawn::enterPipe(PipeEntrance::Type type)
{
    switch(type)
    {
    case PipeEntrance::Type::Left:
        if (state != State::Walking) return false;
        if (left) return false;
        break;
    case PipeEntrance::Type::Top:
        if (state != State::Walking) return false;
        if (!controller.down.get()) return false;
        break;
    default:
        return false;
    }
    state = State::EnterPipe;
    removeCollisionShape();
    render_data.order = -2;
    sp::audio::Sound::play("sfx/smb_pipe.wav");
    return true;
}

void PlayerPawn::die()
{
    if (state == State::Death)
        return;
    sp::audio::Sound::play("sfx/smb_mariodie.wav");
    state = State::Death;
    death_velocity = 0.3;
    removeCollisionShape();
}

void PlayerPawn::setupCollisionShape()
{
    if (animation_prefix == "")
    {
        sp::collision::Box2D shape(12.0/16.0, 14.0/16.0, 0, -1.0/16.0);
        shape.type = sp::collision::Shape::Type::Dynamic;
        shape.setFilterCategory(collision_category_player);
        shape.fixed_rotation = true;
        setCollisionShape(shape);
    }else{
        sp::collision::Box2D shape(12.0/16.0, 12.0/16.0 + 1.0, 0, -2.0/16.0);
        shape.type = sp::collision::Shape::Type::Dynamic;
        shape.setFilterCategory(collision_category_player);
        shape.fixed_rotation = true;
        setCollisionShape(shape);
    }
}

bool PlayerPawn::isInWater()
{
    if (getPosition2D().y < global_area_data.water_level)
        return true;
    return false;
}

bool PlayerPawn::isFinished()
{
    return state == State::Finish && finish_state == FinishSubState::Stopped;
}

sp::P<PlayerPawn> PlayerPawn::getClosestTo(sp::Vector2d position)
{
    sp::P<PlayerPawn> result;
    for(auto player : all)
    {
        if (!result || sp::length(player->getPosition2D() - position) < sp::length(result->getPosition2D() - position))
            result = player;
    }
    return result;
}

#include "buzzyBeetle.h"
#include "../../main.h"

#include <sp2/engine.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/box.h>

//Convert mario subpixel acceleration from subpixels at 60 ups to velocity delta at 30 ups.
// http://photobucket.com/gallery/user/jdaster64/media/bWVkaWFJZDo5MzAyOTA2Nw==/?ref=
static constexpr float subpixelToAcceleration(int subpixel)
{
    return (float(subpixel) / float(0x10000)) * 60.0 * 60.0 / sp::Engine::fixed_update_frequency;
}
//Convert mario subpixel speed from subpixels at 60 ups to units per second.
// http://photobucket.com/gallery/user/jdaster64/media/bWVkaWFJZDo5MzAyOTA2Nw==/?ref=
static constexpr float subpixelToSpeed(int subpixel)
{
    return (float(subpixel) / float(0x10000)) * 60.0;
}

BuzzyBeetle::BuzzyBeetle(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y)
{
    sp::collision::Box2D shape(14.0/16.0, 14.0/16.0, 0, -1.0/16.0);
    shape.type = sp::collision::Shape::Type::Dynamic;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    setAnimation(sp::SpriteAnimation::load("buzzyBeetle.txt"));
    animationPlay("Walk");
    state = State::Normal;
    
    flip = false;
}

void BuzzyBeetle::onEnemyUpdate()
{
    sp::Vector2d velocity = getLinearVelocity2D();

    velocity.y -= subpixelToAcceleration(0x300);
    //Limit falling velocity.
    if (velocity.y < -subpixelToSpeed(0x4000))
        velocity.y = -subpixelToSpeed(0x4000);

    switch(state)
    {
    case State::Normal:
        if (flip)
            velocity.x = subpixelToSpeed(0x800);
        else
            velocity.x = -subpixelToSpeed(0x800);
        break;
    case State::Down:
        velocity.x = 0;
        break;
    case State::Skating:
        if (flip)
            velocity.x = subpixelToSpeed(0x2800);
        else
            velocity.x = -subpixelToSpeed(0x2800);
        break;
    }
    setLinearVelocity(velocity);
    if (flip)
        animationSetFlags(sp::SpriteAnimation::FlipFlag);
    else
        animationSetFlags(0);
}

void BuzzyBeetle::onCollision(sp::CollisionInfo& info)
{
    if (state == State::Skating)
    {
        sp::Vector2d position = getPosition2D();
        sp::Vector2d camera_position = getScene()->getCamera()->getPosition2D();
        sp::P<Enemy> other = info.other;
        if (other)
        {
            if (position.x > camera_position.x + 10)
            {
                //Koopa shell ran out of the screen, it normally would dispear, instead, make it bounch off enemies, by not handling kill logic.
                flip = false;
                return;
            }else{
                other->kill();
                return;
            }
        }
    }
    Enemy::onCollision(info);
}

void BuzzyBeetle::onSideHit(bool left)
{
    flip = left;
}

bool BuzzyBeetle::onPlayerHeadBump()
{
    animationPlay("Death");
    if (state == State::Down)
    {
        state = State::Skating;
        flip = !flip;
    }
    else
    {
        state = State::Down;
    }
    return true;
}

bool BuzzyBeetle::onPlayerSideBump(bool left)
{
    if (state == State::Down)
    {
        state = State::Skating;
        flip = left;
        return true;
    }
    return false;
}

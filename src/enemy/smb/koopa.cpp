#include "koopa.h"
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

Koopa::Koopa(sp::P<sp::Node> parent, float x, float y, Type type, Behaviour behaviour)
: Enemy(parent, x, y), type(type), behaviour(behaviour)
{
    sp::collision::Box2D shape(14.0/16.0, 14.0/16.0, 0, -1.0/16.0);
    shape.type = sp::collision::Shape::Type::Dynamic;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    switch(type)
    {
    case Type::Red:
    case Type::ParatroopaRed:
        animation = sp::SpriteAnimation::load("koopaRed.txt");
        break;
    case Type::Green:
    case Type::ParatroopaGreen:
        animation = sp::SpriteAnimation::load("koopa.txt");
        break;
    }
    
    switch(type)
    {
    case Type::Red:
    case Type::Green:
        animation->play("Walk");
        break;
    case Type::ParatroopaRed:
    case Type::ParatroopaGreen:
        animation->play("ParatroopaWalk");
        break;
    }
    state = State::Normal;
    
    flip = false;
}

void Koopa::onEnemyUpdate()
{
    sp::Vector2d velocity = getLinearVelocity2D();
    sp::Vector2d position = getPosition2D();
    if (start_position.x == 0.0)
        start_position = position;

    switch(behaviour)
    {
    case Behaviour::Walking:
    case Behaviour::WalkingNoEdge:
        velocity.y -= subpixelToAcceleration(0x300);
        //Limit falling velocity.
        if (velocity.y < -subpixelToSpeed(0x4000))
            velocity.y = -subpixelToSpeed(0x4000);
        break;
    case Behaviour::Leaping:
        velocity.y -= subpixelToAcceleration(0x180);
        //Limit falling velocity.
        if (velocity.y < -subpixelToSpeed(0x4000))
            velocity.y = -subpixelToSpeed(0x4000);
        break;
    case Behaviour::FlyingUpDown:
        if (position.y >= start_position.y - 0.5)
        {
            velocity.y -= subpixelToAcceleration(0x040);
        }
        else if (position.y <= start_position.y - 5.5)
        {
            velocity.y += subpixelToAcceleration(0x040);
        }
        else
        {
            if (velocity.y > 0)
                velocity.y = subpixelToSpeed(0x0800);
            else
                velocity.y =-subpixelToSpeed(0x0800);
        }
        velocity.x = 0;
        break;
    case Behaviour::FlyingLeftRight:
        break;
    }

    switch(state)
    {
    case State::Normal:
        if (behaviour == Behaviour::FlyingUpDown || behaviour == Behaviour::FlyingLeftRight)
            break;
        if (behaviour == Behaviour::WalkingNoEdge)
        {
            sp::Vector2d start = position + sp::Vector2d(0.0, -0.40);
            sp::Vector2d end = start + sp::Vector2d(0.0, -0.20);
            
            bool center = false;
            getScene()->queryCollisionAny(sp::Ray2d(start, end), [&center](sp::P<sp::Node> object, sp::Vector2d hit_location, sp::Vector2d hit_normal)
            {
                if (sp::P<sp::Tilemap>(object))
                {
                    center = true;
                    return false;
                }
                return true;
            });
            if (flip)
            {
                start += sp::Vector2d(0.3, 0);
                end += sp::Vector2d(0.3, 0);
            }
            else
            {
                start -= sp::Vector2d(0.3, 0);
                end -= sp::Vector2d(0.3, 0);
            }
            bool side = false;
            getScene()->queryCollisionAny(sp::Ray2d(start, end), [&side](sp::P<sp::Node> object, sp::Vector2d hit_location, sp::Vector2d hit_normal)
            {
                if (sp::P<sp::Tilemap>(object))
                {
                    side = true;
                    return false;
                }
                return true;
            });
            if (center && !side)
                flip = !flip;
        }
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
        animation->setFlags(sp::SpriteAnimation::FlipFlag);
    else
        animation->setFlags(0);
}

void Koopa::onCollision(sp::CollisionInfo& info)
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

void Koopa::onSideHit(bool left)
{
    flip = left;
}

void Koopa::onFloorHit()
{
    if (behaviour == Behaviour::Leaping && getLinearVelocity2D().y <= 0)
        setLinearVelocity(getLinearVelocity2D() + sp::Vector2d(0, 10));
}

bool Koopa::onPlayerHeadBump()
{
    if (behaviour == Behaviour::FlyingUpDown || behaviour == Behaviour::FlyingLeftRight || behaviour == Behaviour::Leaping)
    {
        if (type == Type::ParatroopaRed || type == Type::Red)
            behaviour = Behaviour::WalkingNoEdge;
        else
            behaviour = Behaviour::Walking;
    }
    if (type == Type::ParatroopaGreen)
    {
        type = Type::Green;
        animation->play("Walk");
        return true;
    }
    if (type == Type::ParatroopaRed)
    {
        type = Type::Red;
        animation->play("Walk");
        return true;
    }
    
    animation->play("Death");
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

bool Koopa::onPlayerSideBump(bool left)
{
    if (state == State::Down)
    {
        state = State::Skating;
        flip = left;
        return true;
    }
    return false;
}

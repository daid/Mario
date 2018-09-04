#include "goomba.h"
#include "../../main.h"

#include <sp2/engine.h>
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

Goomba::Goomba(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y)
{
    sp::collision::Box2D shape(14.0/16.0, 14.0/16.0, 0, -1.0/16.0);
    shape.type = sp::collision::Shape::Type::Dynamic;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    
    setCollisionShape(shape);
    
    setAnimation(sp::SpriteAnimation::load("goomba.txt"));
    animationPlay("Walk");
    
    flip = false;
    state = State::Normal;
    state_counter = 60;
    is_small_enemy = true;
}

void Goomba::onEnemyUpdate()
{
    switch(state)
    {
    case State::Normal:{
        sp::Vector2d velocity = getLinearVelocity2D();

        velocity.y -= subpixelToAcceleration(0x700);
        //Limit falling velocity.
        if (velocity.y < -subpixelToSpeed(0x4000))
            velocity.y = -subpixelToSpeed(0x4000);
        
        if (flip)
            velocity.x = subpixelToSpeed(0x800);
        else
            velocity.x = -subpixelToSpeed(0x800);
        setLinearVelocity(velocity);
        }break;
    case State::Death:{
        if (state_counter > 0)
            state_counter--;
        else
            delete this;
        }break;
    }
}

void Goomba::onSideHit(bool left)
{
    flip = left;
}

bool Goomba::onPlayerHeadBump()
{
    removeCollisionShape();
    state = State::Death;
    animationPlay("Death");
    return true;
}

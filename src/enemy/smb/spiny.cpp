#include "spiny.h"
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

Spiny::Spiny(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y)
{
    sp::collision::Box2D shape(14.0/16.0, 14.0/16.0, 0, -1.0/16.0);
    shape.type = sp::collision::Shape::Type::Dynamic;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    setAnimation(sp::SpriteAnimation::load("spiny.txt"));
    animationPlay("Fall");
    
    setLinearVelocity(sp::Vector2d(0, subpixelToSpeed(0x4000)));
    velocity_y_min = subpixelToSpeed(0x4000);
    flip = (getPosition2D().x < getScene()->getCamera()->getPosition2D().x);
}

void Spiny::onEnemyUpdate()
{
    sp::Vector2d velocity = getLinearVelocity2D();

    velocity.y -= subpixelToAcceleration(0x300);
    if (falling)
    {
        if (velocity.y > velocity_y_min)
        {
            falling = false;
            animationPlay("Walk");
            flip = (getPosition2D().x < getScene()->getCamera()->getPosition2D().x);
        }
        velocity_y_min = std::min(velocity_y_min, velocity.y);
    }
    //Limit falling velocity.
    if (velocity.y < -subpixelToSpeed(0x4000))
        velocity.y = -subpixelToSpeed(0x4000);

    if (falling)
    {
        if (flip)
            velocity.x = subpixelToSpeed(0xa00);
        else
            velocity.x = -subpixelToSpeed(0xa00);
    }else{
        if (flip)
            velocity.x = subpixelToSpeed(0x800);
        else
            velocity.x = -subpixelToSpeed(0x800);
    }
    setLinearVelocity(velocity);
    if (flip)
        animationSetFlags(sp::SpriteAnimation::FlipFlag);
    else
        animationSetFlags(0);
}

void Spiny::onSideHit(bool left)
{
    flip = left;
}

bool Spiny::onPlayerHeadBump()
{
    return false;
}

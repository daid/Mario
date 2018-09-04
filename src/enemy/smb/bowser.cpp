#include "bowser.h"
#include "../../fireball2.h"
#include "../../main.h"

#include <sp2/engine.h>
#include <sp2/random.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/box.h>

Bowser::Bowser(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x + 0.5, y + 0.5)
{
    sp::collision::Box2D shape(28.0/16.0, 28.0/16.0, 0, -1.0/16.0);
    shape.type = sp::collision::Shape::Type::Dynamic;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    
    setCollisionShape(shape);
    
    setAnimation(sp::SpriteAnimation::load("bowser.txt"));
    animationPlay("Walk");
}

void Bowser::onEnemyUpdate()
{
    sp::Vector2d velocity = getLinearVelocity2D();
    
    velocity.y -= 0.6;
    //Limit falling velocity.
    if (velocity.y < -14)
        velocity.y = -14;
    
    if (can_jump && velocity.y > 0)
        can_jump = false;
    
    if (can_jump)
    {
        if (sp::random(0, 100) < 4)
        {
            velocity.y += 8;
            can_jump = false;
        }
    }

    sp::Vector2d position = getPosition2D();
    if (start_position.x == 0)
        start_position = position;
    if (can_jump)
    {
        if (position.x < start_position.x - 2)
            velocity.x = 0.9;
        if (position.x > start_position.x + 2)
            velocity.x = -0.9;
        if (std::abs(velocity.x) < 0.1)
            velocity.x = 0.9;
    }
    
    if (fire_delay > 0)
    {
        if (fire_delay < 60)
            animationPlay("PreFire");
        fire_delay--;
    }else{
        animationPlay("Walk");
        fire_delay = sp::irandom(120, 240);
        
        (new Fireball2(getParent(), start_position.y + sp::random(-1, 3)))->setPosition(position + sp::Vector2d(0, 0.5));
    }
    
    setLinearVelocity(velocity);
}

void Bowser::onSideHit(bool left)
{
    if (!left)
        setLinearVelocity(sp::Vector2d(std::abs(getLinearVelocity2D().x), getLinearVelocity2D().y));
    else
        setLinearVelocity(sp::Vector2d(-std::abs(getLinearVelocity2D().x), getLinearVelocity2D().y));
}

bool Bowser::onPlayerHeadBump()
{
    return false;
}

void Bowser::onFloorHit()
{
    can_jump = true;
}

void Bowser::onDeath()
{
    int limit = global_area_data.view_limit / 16;
    limit += 2;
    global_area_data.view_limit = limit * 16;
}

void Bowser::kill()
{
}

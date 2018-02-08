#include "hammerBrother.h"
#include "../../main.h"

#include <sp2/engine.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/box.h>


HammerBrother::HammerBrother(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y)
{
    sp::collision::Box2D shape(14.0/16.0, 0.5 + 14.0/16.0, 0, -1.0/16.0);
    shape.type = sp::collision::Shape::Type::Dynamic;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    
    setCollisionShape(shape);
    
    animation = sp::SpriteAnimation::load("hammerbro.txt");
    animation->play("Walk");

    start_x = x;
}

void HammerBrother::onEnemyUpdate()
{
    sp::Vector2d velocity = getLinearVelocity2D();
    velocity.x = 1.5;
    velocity.y -= 0.3;
    if (getPosition2D().x < start_x - 0.7)
        forward = false;
    if (getPosition2D().x > start_x + 1.0)
        forward = true;
    if (forward)
        velocity.x = -velocity.x;
    setLinearVelocity(velocity);
    
    if (fire_delay < 10)
        animation->play("Walk");
    else
        animation->play("PreFire");
        
    if (fire_delay > 0)
    {
        fire_delay--;
    }
    else
    {
        fire_delay = 40;
    }
    if (jump_delay > 0)
    {
        jump_delay--;
    }
    else
    {
        jump_delay = 200;
    }
}

void HammerBrother::onSideHit(bool left)
{
}

bool HammerBrother::onPlayerHeadBump()
{
    kill();
    return true;
}

#include "blooper.h"
#include "../../playerPawn.h"
#include "../../main.h"

#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/circle.h>


Blooper::Blooper(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y)
{
    sp::collision::Circle2D shape(13.0/32.0);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    animation = sp::SpriteAnimation::load("blooper.txt");
    animation->play("Idle");
}

void Blooper::onEnemyUpdate()
{
    sp::Vector2d velocity = getLinearVelocity2D();
    velocity.y -= 0.1;
    velocity.y = std::max(-4.0, velocity.y);
    if (velocity.x > 0)
        velocity.x -= 0.1;
    if (velocity.x < 0)
        velocity.x += 0.1;
    
    if (delay > 0)
    {
        delay --;
    }
    else
    {
        delay = 40;
        sp::P<PlayerPawn> player = PlayerPawn::getClosestTo(getPosition2D());
        if (!player)
        {
            if (getPosition2D().y < 8)
                velocity.y = 4.0;
            else
                velocity.y = 2.0;
        }
        else
        {
            if (getPosition2D().y < player->getPosition2D().y + 2)
            {
                velocity.y = 4.0;
                if (getPosition2D().x < player->getPosition2D().x)
                    velocity.x = 4.0;
                else
                    velocity.x =-4.0;
            }
            else
            {
                velocity.y = 2.0;
                delay = 80;
            }
        }
    }
    if (delay < 20)
        animation->play("Compress");
    else
        animation->play("Idle");
    
    setLinearVelocity(velocity);
}

void Blooper::onSideHit(bool left)
{
}

bool Blooper::onPlayerHeadBump()
{
    kill();
    return true;
}

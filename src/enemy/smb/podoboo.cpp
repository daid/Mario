#include "podoboo.h"
#include "../../playerPawn.h"
#include "../../main.h"

#include <sp2/engine.h>
#include <sp2/scene/scene.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/box.h>


Podoboo::Podoboo(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y - 0.75)
{
    sp::collision::Box2D shape(14.0/16.0, 14.0/16.0);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    
    setCollisionShape(shape);
    
    animation = sp::SpriteAnimation::load("podoboo.txt");
    animation->play("Default");
    
    render_data.order = 1;
}

void Podoboo::onEnemyUpdate()
{
    sp::Vector2d position = getPosition2D();
    sp::Vector2d velocity = getLinearVelocity2D();
    if (position.y < -1.5)
        velocity = sp::Vector2d(0, 13.5);
    velocity.y += -0.3;
    if (velocity.y > 0)
        setRotation(0);
    else
        setRotation(180);
    setLinearVelocity(velocity);
}

void Podoboo::onSideHit(bool left)
{
}

bool Podoboo::onPlayerHeadBump()
{
    return false;
}

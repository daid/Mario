#include "lakitu.h"
#include "spiny.h"
#include "../../playerPawn.h"
#include "../../main.h"

#include <sp2/random.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/box.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>


Lakitu::Lakitu(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y)
{
    sp::collision::Box2D shape(13.0/16.0, 13.0/16.0);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    animation = sp::SpriteAnimation::load("lakitu.txt");
    animation->play("Default");
}

void Lakitu::onEnemyUpdate()
{
    double position_offset = getPosition2D().x - getScene()->getCamera()->getPosition2D().x;
    sp::Vector2d velocity = getLinearVelocity2D();
    if (position_offset > 6)
        setLinearVelocity(sp::Vector2d(-2.5, 0));
    if (position_offset < -4 && velocity.x < 3.5)
        setLinearVelocity(sp::Vector2d(3.5, 0));
    if (position_offset < -6 && velocity.x < 5.5)
        setLinearVelocity(sp::Vector2d(5.5, 0));
    if (position_offset < -8 && velocity.x < 15.5)
        setLinearVelocity(sp::Vector2d(15.5, 0));
    
    if (throw_delay < 40)
        animation->play("PreFire");
    else
        animation->play("Default");
    
    if (throw_delay > 0)
    {
        throw_delay--;
    }
    else
    {
        new Spiny(getParent(), getPosition2D().x, getPosition2D().y);
        throw_delay = 200;
    }
}

void Lakitu::onSideHit(bool left)
{
}

bool Lakitu::onPlayerHeadBump()
{
    animation->play("Default");
    kill();
    return true;
}

#include "piranhaPlant.h"
#include "../../playerPawn.h"
#include "../../main.h"

#include <sp2/engine.h>
#include <sp2/scene/scene.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/box.h>


PiranhaPlant::PiranhaPlant(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y - 0.75)
{
    sp::collision::Box2D shape(12.0/16.0, 16.0/16.0, 0, -4.0/16.0);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    
    setCollisionShape(shape);
    
    setAnimation(sp::SpriteAnimation::load("piranhaPlant.txt"));
    animationPlay("Default");
    
    render_data.order = -2;
}

void PiranhaPlant::onEnemyUpdate()
{
    sp::Vector2d position = getPosition2D();
    if (start_position.x == 0)
        start_position = position;
    if (position.y <= start_position.y)
    {
        if (playerNear())
        {
            setLinearVelocity(sp::Vector2d(0, 0));
            setPosition(start_position);
        }
        else
        {
            setLinearVelocity(sp::Vector2d(0, 1));
        }
    }
    if (position.y >= start_position.y + 2)
        setLinearVelocity(sp::Vector2d(0, -1));
}

void PiranhaPlant::onSideHit(bool left)
{
}

bool PiranhaPlant::onPlayerHeadBump()
{
    return false;
}

bool PiranhaPlant::playerNear()
{
    sp::Vector2d position = getPosition2D();
    sp::Vector2d start(position.x - 1, 0);
    sp::Vector2d end(position.x + 1, 14);
    bool has_player = false;
    getScene()->queryCollision(start, end, [&has_player](sp::P<sp::Node> object)
    {
        if (sp::P<PlayerPawn>(object))
        {
            has_player = true;
            return false;
        }
        return true;
    });
    return has_player;
}

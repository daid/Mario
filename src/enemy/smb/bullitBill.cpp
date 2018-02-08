#include "bullitBill.h"
#include "../../playerPawn.h"
#include "../../main.h"

#include <sp2/random.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/box.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>


BullitBill::BullitBill(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y)
{
    sp::collision::Box2D shape(13.0/16.0, 13.0/16.0);
    shape.type = sp::collision::Shape::Type::Kinematic;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    animation = sp::SpriteAnimation::load("bullitBill.txt");
    animation->play("Default");
    setLinearVelocity(sp::Vector2d(-4.0, 0));
}

void BullitBill::onEnemyUpdate()
{
}

void BullitBill::onSideHit(bool left)
{
}

bool BullitBill::onPlayerHeadBump()
{
    kill();
    return true;
}

BullitGenerator::BullitGenerator(sp::P<sp::Node> parent, float x, float y)
: sp::Node(parent), x(x), y(y), spawn_delay(0.5)
{
}

void BullitGenerator::onUpdate(float delta)
{
    sp::Vector2d camera_position = getScene()->getCamera()->getPosition2D();
    if (std::abs(camera_position.x - x) > 8)
        return;

    if (spawn_delay > 0)
    {
        spawn_delay -= delta;
    }
    else
    {
        new BullitBill(getParent(), x, y);
        spawn_delay = 3.0;
    }
}

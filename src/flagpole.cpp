#include "flagpole.h"

#include "playerPawn.h"

#include <sp2/collision/2d/box.h>

Flagpole::Flagpole(sp::P<sp::Node> parent, double x)
: sp::Node(parent)
{
    sp::collision::Box2D shape(0.3, 20);
    shape.type = sp::collision::Shape::Type::Sensor;
    setCollisionShape(shape);
    
    setPosition(sp::Vector2d(x, 10));
}

void Flagpole::onCollision(sp::CollisionInfo& info)
{
    sp::P<PlayerPawn> player = info.other;
    if (player)
    {
        player->gotFlagpole(getPosition2D().x);
    }
}

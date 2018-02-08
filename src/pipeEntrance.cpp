#include "pipeEntrance.h"
#include "playerPawn.h"
#include <sp2/collision/2d/box.h>

sp::P<PipeEntrance> PipeEntrance::active_entrance;

PipeEntrance::PipeEntrance(sp::P<sp::Node> parent, Type type, std::function<void()> func)
: sp::Node(parent), func(func), type(type)
{
    switch(type)
    {
    case Type::Top:{
        sp::collision::Box2D shape(1, 1.1);
        shape.type = sp::collision::Shape::Type::Sensor;
        setCollisionShape(shape);
        }break;
    case Type::Left:{
        sp::collision::Box2D shape(1.1, 1.5);
        shape.type = sp::collision::Shape::Type::Sensor;
        setCollisionShape(shape);
        }break;
    }
}

void PipeEntrance::onCollision(sp::CollisionInfo& info)
{
    sp::P<PlayerPawn> player = info.other;
    if (player && (!active_entrance || active_entrance == this))
    {
        if (player->enterPipe(type))
        {
            active_entrance = this;
        }
    }
}

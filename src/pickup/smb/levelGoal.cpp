#include "levelGoal.h"

#include "../../playerPawn.h"

#include <sp2/collision/2d/circle.h>
#include <sp2/graphics/spriteAnimation.h>


LevelGoalPickup::LevelGoalPickup(sp::P<sp::Node> parent, Type type)
: sp::Node(parent)
{
    sp::collision::Circle2D shape(2.5);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.fixed_rotation = true;
    setCollisionShape(shape);

    setAnimation(sp::SpriteAnimation::load("upgrade.txt"));
    switch(type)
    {
    case Type::Toad:
        animationPlay("Toad");
        break;
    case Type::Princess:
        animationPlay("Princess");
        break;
    }
    
    render_data.order = -2;
}

void LevelGoalPickup::onCollision(sp::CollisionInfo& info)
{
    if (bool(info.other) && info.other->isSolid())
    {
        sp::P<PlayerPawn> player = info.other;
        if (player)
        {
            player->finish();
        }
    }
}

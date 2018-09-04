#include "upgrade.h"

#include "../../playerPawn.h"

#include <sp2/graphics/spriteAnimation.h>


UpgradePickup::UpgradePickup(sp::P<sp::Node> parent, Type type)
: Pickup(parent, type == Type::Mushroom ? Pickup::Movement::Slide : Pickup::Movement::Still)
{
    setAnimation(sp::SpriteAnimation::load("upgrade.txt"));
    switch(type)
    {
    case Type::Mushroom:
        animationPlay("Mushroom");
        break;
    case Type::Flower:
        animationPlay("Flower");
        break;
    }
}

bool UpgradePickup::onPickup(sp::P<PlayerPawn> player)
{
    return player->upgrade();
}

#include "upgrade.h"

#include "../../playerPawn.h"

#include <sp2/graphics/spriteAnimation.h>


UpgradePickup::UpgradePickup(sp::P<sp::Node> parent, Type type)
: Pickup(parent, type == Type::Mushroom ? Pickup::Movement::Slide : Pickup::Movement::Still)
{
    animation = sp::SpriteAnimation::load("upgrade.txt");
    switch(type)
    {
    case Type::Mushroom:
        animation->play("Mushroom");
        break;
    case Type::Flower:
        animation->play("Flower");
        break;
    }
}

bool UpgradePickup::onPickup(sp::P<PlayerPawn> player)
{
    return player->upgrade();
}

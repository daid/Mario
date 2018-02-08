#include "star.h"

#include "../../playerPawn.h"

#include <sp2/graphics/spriteAnimation.h>


StarPickup::StarPickup(sp::P<sp::Node> parent)
: Pickup(parent, Pickup::Movement::Bounce)
{
    animation = sp::SpriteAnimation::load("upgrade.txt");
    animation->play("Star");
}

bool StarPickup::onPickup(sp::P<PlayerPawn> player)
{
    player->setInvincibilityTime(10, true);
    return true;
}

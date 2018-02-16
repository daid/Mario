#include "life.h"

#include "../../playerPawn.h"
#include "../../main.h"
#include "../../saveGame.h"

#include <sp2/graphics/spriteAnimation.h>
#include <sp2/audio/sound.h>


LifePickup::LifePickup(sp::P<sp::Node> parent)
: Pickup(parent, Pickup::Movement::Slide)
{
    animation = sp::SpriteAnimation::load("upgrade.txt");
    animation->play("Life");
}

bool LifePickup::onPickup(sp::P<PlayerPawn> player)
{
    sp::audio::Sound::play("sfx/smb_1-up.wav");
    //respawnPlayer();
    save_game.addLife();
    return true;
}

#include "coin.h"
#include "main.h"
#include "playerPawn.h"

#include <sp2/collision/2d/box.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/audio/sound.h>

Coin::Coin(sp::P<sp::Node> parent)
: sp::Node(parent)
{
    sp::collision::Box2D shape(0.6, 0.6);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.setFilterCategory(collision_category_pickup);
    shape.fixed_rotation = true;
    
    animation = sp::SpriteAnimation::load("coin.txt");
    animation->play("Default");

    setCollisionShape(shape);
    
    render_data.order = -1;
}

void Coin::onCollision(sp::CollisionInfo& info)
{
    sp::P<PlayerPawn> player = info.other;
    if (player)
    {
        sp::audio::Sound::play("sfx/smb_coin.wav");
        delete this;
    }
}

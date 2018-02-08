#include "fireball2.h"
#include "playerPawn.h"

#include <sp2/engine.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>
#include <sp2/collision/2d/box.h>
#include <sp2/audio/sound.h>
#include <sp2/graphics/spriteAnimation.h>


Fireball2::Fireball2(sp::P<sp::Node> parent, double target_y)
: sp::Node(parent), target_y(target_y)
{
    sp::collision::Box2D shape(1, 0.25);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.fixed_rotation = true;
    setCollisionShape(shape);

    animation = sp::SpriteAnimation::load("fireball2.txt");
    animation->play("Default");

    render_data.order = 2;
    
    sp::audio::Sound::play("sfx/smb_bowserfire.wav");
}

void Fireball2::onFixedUpdate()
{
    sp::Vector2d position = getPosition2D();
    sp::Vector2d camera_position = getScene()->getCamera()->getPosition2D();

    if (position.y < -2.0 || std::abs(position.x - camera_position.x) > 10)
    {
        delete this;
        return;
    }
    if (target_y < 0)
        target_y = position.y;

    sp::Vector2d velocity = getLinearVelocity2D();
    velocity.x = -5;
    if (position.y < target_y - 0.3)
        velocity.y = 2.5;
    else if (position.y > target_y + 0.3)
        velocity.y = -2.5;
    else
        velocity.y = 0;
    setLinearVelocity(velocity);
}

void Fireball2::onCollision(sp::CollisionInfo& info)
{
    if (bool(info.other) && info.other->isSolid())
    {
        sp::P<PlayerPawn> player = info.other;
        if (player)
            player->takeDamage();
    }
}

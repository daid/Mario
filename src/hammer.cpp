#include "hammer.h"
#include "main.h"
#include "playerPawn.h"

#include <sp2/collision/2d/circle.h>
#include <sp2/graphics/spriteAnimation.h>


Hammer::Hammer(sp::P<sp::Node> parent, double x, double y)
: sp::Node(parent)
{
    setAnimation(sp::SpriteAnimation::load("hammer.txt"));
    animationPlay("Default");

    render_data.order = 2;

    sp::collision::Circle2D shape(0.25);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    setPosition(sp::Vector2d(x, y));
    setLinearVelocity(sp::Vector2d(-4, 15));
}

void Hammer::onUpdate(float delta)
{
    sp::Vector2d velocity = getLinearVelocity2D();
    velocity.y -= delta * 60;
    setLinearVelocity(velocity);
    
    if (getPosition2D().y < -1)
        delete this;
}

void Hammer::onCollision(sp::CollisionInfo& info)
{
    if (bool(info.other) && info.other->isSolid())
    {
        sp::P<PlayerPawn> player = info.other;
        if (player)
            player->takeDamage();
    }
}

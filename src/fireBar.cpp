#include "fireBar.h"
#include "playerPawn.h"

#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/box.h>

FireBar::FireBar(sp::P<sp::Node> parent, Type type, Size size)
: sp::Node(parent), type(type)
{
    if (size == Size::Default)
    {
        sp::collision::Box2D shape(3.0, 0.5, 1.25, 0.0);
        shape.type = sp::collision::Shape::Type::Sensor;
        setCollisionShape(shape);
    }
    else
    {
        sp::collision::Box2D shape(6.0, 0.5, 2.75, 0.0);
        shape.type = sp::collision::Shape::Type::Sensor;
        setCollisionShape(shape);
    }
    setRotation(-90);

    setAnimation(sp::SpriteAnimation::load("fireBar.txt"));
    if (size == Size::Default)
        animationPlay("Default");
    else
        animationPlay("Long");
    
    render_data.order = 1;
}

void FireBar::onFixedUpdate()
{
    switch(type)
    {
    case Type::Left:
        setRotation(getRotation2D() + 1.25);
        break;
    case Type::Right:
        setRotation(getRotation2D() - 1.25);
        break;
    case Type::RightFast:
        setRotation(getRotation2D() - 2);
        break;
    }
}

void FireBar::onCollision(sp::CollisionInfo& info)
{
    sp::P<PlayerPawn> player = info.other;
    if (player)
        player->takeDamage();
}

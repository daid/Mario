#include "lift.h"
#include "playerPawn.h"

#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/box.h>
#include <sp2/scene/scene.h>

Lift::Lift(sp::P<sp::Node> parent, Type type, Size size)
: sp::Node(parent), type(type)
{
    animation = sp::SpriteAnimation::load("lift.txt");

    switch(size)
    {
    case Size::Default:{
        this->size = sp::Vector2d(3.0, 0.5);
        animation->play("Default");
        }break;
    case Size::Small:{
        this->size = sp::Vector2d(2.0, 0.5);
        animation->play("Small");
        }break;
    case Size::Tiny:{
        this->size = sp::Vector2d(1.5, 0.5);
        animation->play("Tiny");
        }break;
    }

    sp::collision::Box2D shape(this->size.x, this->size.y);
    shape.type = sp::collision::Shape::Type::Kinematic;
    shape.fixed_rotation = true;
    setCollisionShape(shape);
}

void Lift::onFixedUpdate()
{
    sp::Vector2d position = getPosition2D();
    if (start_position.x == 0.0)
        start_position = position;
    switch(type)
    {
    case Type::Up:
        if (position.y < 13)
            setPosition(position + sp::Vector2d(0, 1.0/32.0));
        else
            setPosition(sp::Vector2d(position.x, -1.0));
        break;
    case Type::Down:
        if (position.y > -1)
            setPosition(position - sp::Vector2d(0, 1.0/32.0));
        else
            setPosition(sp::Vector2d(position.x, 13.0));
        break;
    case Type::UpDown:
        if (start_position.y < 6)
            start_position.y += 6.0;
        if (position.y >= start_position.y)
            setLinearVelocity(sp::Vector2d(0, -2));
        if (position.y <= 3)
            setLinearVelocity(sp::Vector2d(0, 2));
        break;
    case Type::LeftRight:
        if (position.x >= start_position.x)
            setLinearVelocity(sp::Vector2d(-1, 0));
        if (position.x <= start_position.x - 4.5)
            setLinearVelocity(sp::Vector2d(1, 0));
        break;
    case Type::Fall:{
        bool has_player = false;
        getScene()->queryCollision(getPosition2D() - size * 0.5 + sp::Vector2d(0, 0.2), getPosition2D() + size * 0.5 + sp::Vector2d(0, 0.2), [&has_player](sp::P<sp::Node> node)
        {
            if (sp::P<PlayerPawn>(node))
            {
                has_player = true;
                return false;
            }
            return true;
        });
        if (has_player)
            setLinearVelocity(sp::Vector2d(0, -2));
        else
            setLinearVelocity(sp::Vector2d(0, 0));
        }break;
    case Type::Surfing:
        break;
    case Type::Balance:
        if (other)
        {
            bool has_player1 = false;
            bool has_player2 = false;
            getScene()->queryCollision(getPosition2D() - size * 0.5 + sp::Vector2d(0, 0.2), getPosition2D() + size * 0.5 + sp::Vector2d(0, 0.2), [&has_player1](sp::P<sp::Node> node)
            {
                if (sp::P<PlayerPawn>(node))
                {
                    has_player1 = true;
                    return false;
                }
                return true;
            });
            getScene()->queryCollision(other->getPosition2D() - other->size * 0.5 + sp::Vector2d(0, 0.2), other->getPosition2D() + other->size * 0.5 + sp::Vector2d(0, 0.2), [&has_player2](sp::P<sp::Node> node)
            {
                if (sp::P<PlayerPawn>(node))
                {
                    has_player2 = true;
                    return false;
                }
                return true;
            });

            if (has_player1 && has_player2)
                has_player1 = has_player2 = false;
            if (getPosition2D().y < 2 || other->getPosition2D().y > 10)
                has_player1 = false;
            if (other->getPosition2D().y < 2 || getPosition2D().y > 10)
                has_player2 = false;

            if (has_player1)
            {
                setLinearVelocity(sp::Vector2d(0, -2));
                other->setLinearVelocity(sp::Vector2d(0, 2));
            }
            else if (has_player2)
            {
                setLinearVelocity(sp::Vector2d(0, 2));
                other->setLinearVelocity(sp::Vector2d(0, -2));
            }
            else
            {
                setLinearVelocity(sp::Vector2d(0, 0));
                other->setLinearVelocity(sp::Vector2d(0, 0));
            }
        }
        break;
    }
}

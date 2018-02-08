#include "pickup.h"

#include "../playerPawn.h"
#include "../main.h"

#include <sp2/engine.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>
#include <sp2/collision/2d/circle.h>
#include <sp2/graphics/spriteAnimation.h>


Pickup::Pickup(sp::P<sp::Node> parent, Movement movement)
: sp::Node(parent), movement(movement)
{
    sp::collision::Circle2D shape(0.5);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.setFilterCategory(collision_category_pickup);
    shape.setMaskFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    shape.density = 0.1;
    setCollisionShape(shape);
    
    render_data.order = -2;
}

void Pickup::onFixedUpdate()
{
    sp::Vector2d position = getPosition2D();
    sp::Vector2d camera_position = getScene()->getCamera()->getPosition2D();

    if (position.y < -2.0 || std::abs(position.x - camera_position.x) > 20)
    {
        delete this;
        return;
    }

    double delta = sp::Engine::fixed_update_delta;
    switch(state)
    {
    case State::Rise:
        rise_level += delta;
        setPosition(getPosition2D() + sp::Vector2d(0, delta));
        if (rise_level >= 12.0/16.0)
        {
            state = State::Move;
            
            if (movement != Movement::Still)
            {
                sp::collision::Circle2D shape(0.5);
                shape.type = sp::collision::Shape::Type::Dynamic;
                shape.setFilterCategory(collision_category_pickup);
                shape.setMaskFilterCategory(collision_category_enemy);
                shape.fixed_rotation = true;
                setCollisionShape(shape);
            }
            if (movement == Movement::Bounce)
            {
                setLinearVelocity(sp::Vector2d(0, 4));
            }

            render_data.order = 1;
        }
        break;
    case State::Move:{
        sp::Vector2d velocity = getLinearVelocity2D();

        switch(movement)
        {
        case Movement::Still:
            break;
        case Movement::Slide:
        case Movement::Bounce:
            velocity.y -= 65.0 * delta;
            //Limit falling velocity.
            if (velocity.y < -14)
                velocity.y = -14;
            
            if (movement == Movement::Bounce)
                velocity.x = 4;
            else
                velocity.x = 3;

            if (flip)
                velocity.x = -velocity.x;

            setLinearVelocity(velocity);
            break;
        }
        }break;
    }
}

void Pickup::onCollision(sp::CollisionInfo& info)
{
    if (bool(info.other) && info.other->isSolid())
    {
        sp::P<PlayerPawn> player = info.other;
        if (player)
        {
            if (onPickup(player))
            {
                delete this;
                return;
            }
        }
        
        if (state == State::Move)
        {
            if (info.normal.x <= -0.9)
                flip = false;
            if (info.normal.x >= 0.9)
                flip = true;
            if (info.normal.y < -0.7)
            {
                if (movement == Movement::Bounce)
                {
                    sp::Vector2d velocity = getLinearVelocity2D();
                    velocity.y = info.other->getLinearVelocity2D().y + 16;
                    setLinearVelocity(velocity);
                }
            }
        }
    }
}

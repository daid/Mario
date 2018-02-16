#include "fireball.h"
#include "enemy/enemy.h"
#include "main.h"

#include <sp2/engine.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>
#include <sp2/collision/2d/circle.h>
#include <sp2/graphics/spriteAnimation.h>


Fireball::Fireball(sp::P<sp::Node> parent, bool left)
: sp::Node(parent), left(left)
{
    sp::collision::Circle2D shape(0.25);
    shape.type = sp::collision::Shape::Type::Dynamic;
    shape.fixed_rotation = true;
    shape.setMaskFilterCategory(collision_category_player);
    setCollisionShape(shape);

    animation = sp::SpriteAnimation::load("fireball.txt");
    animation->play("Default");

    render_data.order = 2;
}

void Fireball::onFixedUpdate()
{
    sp::Vector2d position = getPosition2D();
    sp::Vector2d camera_position = getScene()->getCamera()->getPosition2D();

    if (position.y < -2.0 || std::abs(position.x - camera_position.x) > 10)
    {
        delete this;
        return;
    }

    double delta = sp::Engine::fixed_update_delta;
    sp::Vector2d velocity = getLinearVelocity2D();
    velocity.y -= 65.0 * delta;
    //Limit falling velocity.
    if (velocity.y < -14)
        velocity.y = -14;
    
    velocity.x = 15;
    if (left)
        velocity.x = -velocity.x;

    setLinearVelocity(velocity);
}

void Fireball::onCollision(sp::CollisionInfo& info)
{
    if (bool(info.other) && info.other->isSolid())
    {
        sp::P<Enemy> enemy = info.other;
        if (enemy)
        {
            enemy->killByFireball();
            delete this;
            return;
        }
        if (left && info.normal.x <= -0.9)
            delete this;
        if (!left && info.normal.x >= 0.9)
            delete this;
        if (info.normal.y < -0.7)
        {
            sp::Vector2d velocity = getLinearVelocity2D();
            velocity.y = info.other->getLinearVelocity2D().y + 8;
            setLinearVelocity(velocity);
        }
    }
}

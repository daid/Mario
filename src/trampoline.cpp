#include "trampoline.h"
#include "playerPawn.h"

#include <sp2/scene/scene.h>
#include <sp2/collision/2d/box.h>
#include <sp2/graphics/spriteAnimation.h>

Trampoline::Trampoline(sp::P<sp::Node> parent)
: sp::Node(parent)
{
    sp::collision::Box2D shape(1.0, 15.0 / 16, 0, -9.0 / 16.0);
    shape.type = sp::collision::Shape::Type::Static;
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    setAnimation(sp::SpriteAnimation::load("trampoline.txt"));
    animationPlay("Default");
}

void Trampoline::onUpdate(float delta)
{
    sp::Vector2d position = getPosition2D();
    double compress_distance = 1.0;
    for(double f = -0.4; f <= 0.4; f += 0.4)
    {
        getScene()->queryCollisionAll(sp::Ray2d(position - sp::Vector2d(-f, 0.8), position + sp::Vector2d(f, 1)),
            [this, &compress_distance](sp::P<sp::Node> object, sp::Vector2d hit_location, sp::Vector2d hit_normal)
            {
                sp::P<PlayerPawn> player = object;
                if (player)
                {
                    compress_distance = std::min(compress_distance, hit_location.y - getPosition2D().y);
                    return false;
                }
                return true;
            });
    }
    if (compress_distance < 0.5)
        animationPlay("Compressed");
    else if (compress_distance < 1.0)
        animationPlay("Partial");
    else
        animationPlay("Default");
    
    if (compress_distance < 0.0)
    {
        for(double f = -0.4; f <= 0.4; f += 0.4)
        {
            getScene()->queryCollisionAll(sp::Ray2d(position - sp::Vector2d(-f, 0.8), position + sp::Vector2d(f, 1)),
                [this, &compress_distance](sp::P<sp::Node> object, sp::Vector2d hit_location, sp::Vector2d hit_normal)
                {
                    sp::P<PlayerPawn> player = object;
                    if (player)
                        player->trampolineFire();
                    return true;
                });
        }
    }
}

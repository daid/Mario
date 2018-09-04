#include "cheepCheep.h"
#include "../../playerPawn.h"
#include "../../main.h"

#include <sp2/random.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/circle.h>


CheepCheep::CheepCheep(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y)
{
    sp::collision::Circle2D shape(13.0/32.0);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    setAnimation(sp::SpriteAnimation::load("cheepCheep.txt"));
    if (sp::random(0, 100) < 30)
    {
        animationPlay("Red");
        setLinearVelocity(sp::Vector2d(-1.5, 0));
    }
    else
    {
        animationPlay("Grey");
        setLinearVelocity(sp::Vector2d(-1, 0));
    }
}

void CheepCheep::onEnemyUpdate()
{
}

void CheepCheep::onSideHit(bool left)
{
}

bool CheepCheep::onPlayerHeadBump()
{
    kill();
    return true;
}

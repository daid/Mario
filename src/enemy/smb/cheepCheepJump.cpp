#include "cheepCheepJump.h"
#include "../../playerPawn.h"
#include "../../main.h"

#include <sp2/random.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/collision/2d/circle.h>


CheepCheepJump::CheepCheepJump(sp::P<sp::Node> parent, float x, float y)
: Enemy(parent, x, y)
{
    sp::collision::Circle2D shape(13.0/32.0);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.setFilterCategory(collision_category_enemy);
    shape.fixed_rotation = true;
    setCollisionShape(shape);
    
    animation = sp::SpriteAnimation::load("cheepCheep.txt");
    animation->play("Red");
    setLinearVelocity(sp::Vector2d(sp::random(-7, 7), 18));
    if (getLinearVelocity2D().x > 0)
        animation->setFlags(sp::SpriteAnimation::FlipFlag);
}

void CheepCheepJump::onEnemyUpdate()
{
    setLinearVelocity(getLinearVelocity2D() - sp::Vector2d(0, 0.5));
}

void CheepCheepJump::onSideHit(bool left)
{
}

bool CheepCheepJump::onPlayerHeadBump()
{
    kill();
    return true;
}

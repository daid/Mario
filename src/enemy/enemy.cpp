#include "enemy.h"
#include "../playerPawn.h"

#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>

Enemy::Enemy(sp::P<sp::Node> parent, float x, float y)
: sp::Node(parent)
{
    setPosition(sp::Vector2d(x + 0.5, y + 0.5));
}

void Enemy::onFixedUpdate()
{
    sp::Vector2d position = getPosition2D();
    sp::Vector2d camera_position = getScene()->getCamera()->getPosition2D();

    if (killed)
    {
        position.y += killed_velocity;
        killed_velocity -= 0.05;
        setPosition(position);
    }
    
    if (position.y < -2.0 || position.x < camera_position.x - 20)
    {
        if (!killed) onDeath();
        delete this;
        return;
    }
    if (std::abs(position.x - camera_position.x) < 10)
        active = true;
    else if (!active)
        setLinearVelocity(sp::Vector2d(0, 0));
    if (!killed && active)
        onEnemyUpdate();
}

void Enemy::onCollision(sp::CollisionInfo& info)
{
    if (active && bool(info.other) && info.other->isSolid() && (info.force > 0 || !isSolid()))
    {
        sp::P<PlayerPawn> player = info.other;
        if (player)
        {
            sp::Vector2d velocity_difference = getLinearVelocity2D() - player->getLinearVelocity2D();
            if (velocity_difference.y > 0.1 || info.normal.y > 0.9)
            {
                if (!player->isInWater() && onPlayerHeadBump())
                    player->didHeadBump();
                else
                    player->takeDamage();
            }
            else
            {
                if (!onPlayerSideBump(info.normal.x < 0))
                    player->takeDamage();
            }
        }
        else
        {
            if (info.normal.x <= -0.9)
                onSideHit(true);
            if (info.normal.x >= 0.9)
                onSideHit(false);
            if (info.normal.y < -0.9)
                onFloorHit();
        }
    }
}

void Enemy::kill()
{
    onDeath();
    removeCollisionShape();
    setRotation(180);
    killed = true;
    active = false;
}

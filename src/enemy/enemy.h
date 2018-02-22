#ifndef ENEMY_H
#define ENEMY_H

#include <sp2/scene/node.h>


class Enemy : public sp::Node
{
public:
    Enemy(sp::P<sp::Node> parent, float x, float y);

    virtual void onFixedUpdate() override;
    virtual void onCollision(sp::CollisionInfo& info) override;

    virtual void onEnemyUpdate() = 0;
    virtual void onSideHit(bool left) = 0;
    virtual void onFloorHit() {}
    virtual bool onPlayerHeadBump() = 0;
    virtual bool onPlayerSideBump(bool left) { return false; }
    virtual void onDeath() {}
    
    virtual void kill();
    virtual void killByFireball() { kill(); }

    double extra_trigger_distance = 0;
protected:
    bool is_small_enemy = false;
private:
    bool killed = false;
    bool active = false;
    double killed_velocity = 0.3;
};

#endif//ENEMY_H

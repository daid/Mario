#ifndef SMB_BUZZY_BEETLE_H
#define SMB_BUZZY_BEETLE_H

#include "../enemy.h"
#include <sp2/scene/tilemap.h>

class BuzzyBeetle : public Enemy
{
public:
    BuzzyBeetle(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate() override;
    virtual void onCollision(sp::CollisionInfo& info) override;
    virtual void onSideHit(bool left) override;
    virtual bool onPlayerHeadBump() override;
    virtual bool onPlayerSideBump(bool left) override;

    virtual void killByFireball() override {}
private:
    bool flip;

    enum class State
    {
        Normal,
        Down,
        Skating
    } state;
};

#endif//SMB_BUZZY_BEETLE_H

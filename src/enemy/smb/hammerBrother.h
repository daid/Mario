#ifndef ENEMY_SMB_HAMMER_BROTHER_H
#define ENEMY_SMB_HAMMER_BROTHER_H

#include "../enemy.h"

class HammerBrother : public Enemy
{
public:
    HammerBrother(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate() override;
    virtual void onSideHit(bool left) override;
    virtual bool onPlayerHeadBump() override;
private:
    float start_x;
    bool forward = true;
    int jump_delay = 200;
    int fire_delay = 30;
};

#endif//ENEMY_SMB_HAMMER_BROTHER_H

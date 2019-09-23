#ifndef ENEMY_SMB_PODOBOO_H
#define ENEMY_SMB_PODOBOO_H

#include "../enemy.h"

class Podoboo : public Enemy
{
public:
    Podoboo(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate() override;
    virtual void onSideHit(bool left) override;
    virtual bool onPlayerHeadBump() override;
};

#endif//ENEMY_SMB_PODOBOO_H

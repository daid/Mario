#ifndef ENEMY_SMB_LAKITU_H
#define ENEMY_SMB_LAKITU_H

#include "../enemy.h"

class Lakitu : public Enemy
{
public:
    Lakitu(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate();
    virtual void onSideHit(bool left);
    virtual bool onPlayerHeadBump();

private:
    int throw_delay = 100;
};

#endif//ENEMY_SMB_LAKITU_H

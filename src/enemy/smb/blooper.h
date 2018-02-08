#ifndef ENEMY_SMB_BLOOPER_H
#define ENEMY_SMB_BLOOPER_H

#include "../enemy.h"

class Blooper : public Enemy
{
public:
    Blooper(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate();
    virtual void onSideHit(bool left);
    virtual bool onPlayerHeadBump();

private:
    int delay = 0;
};

#endif//ENEMY_SMB_BLOOPER_H

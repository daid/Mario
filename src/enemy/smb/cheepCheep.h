#ifndef ENEMY_SMB_CHEEP_CHEEP_H
#define ENEMY_SMB_CHEEP_CHEEP_H

#include "../enemy.h"

class CheepCheep : public Enemy
{
public:
    CheepCheep(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate();
    virtual void onSideHit(bool left);
    virtual bool onPlayerHeadBump();

private:
};

#endif//ENEMY_SMB_CHEEP_CHEEP_H

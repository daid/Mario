#ifndef ENEMY_SMB_CHEEP_CHEEP_JUMP_H
#define ENEMY_SMB_CHEEP_CHEEP_JUMP_H

#include "../enemy.h"

class CheepCheepJump : public Enemy
{
public:
    CheepCheepJump(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate() override;
    virtual void onSideHit(bool left) override;
    virtual bool onPlayerHeadBump() override;

private:
};

#endif//ENEMY_SMB_CHEEP_CHEEP_JUMP_H

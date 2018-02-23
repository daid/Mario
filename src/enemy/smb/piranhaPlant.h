#ifndef ENEMY_SMB_PIRANHA_PLANT_H
#define ENEMY_SMB_PIRANHA_PLANT_H

#include "../enemy.h"

class PiranhaPlant : public Enemy
{
public:
    PiranhaPlant(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate();
    virtual void onSideHit(bool left);
    virtual bool onPlayerHeadBump();

private:
    sp::Vector2d start_position;
    
    bool playerNear();
};

#endif//ENEMY_SMB_PIRANHA_PLANT_H

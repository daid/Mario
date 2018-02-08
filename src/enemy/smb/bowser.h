#ifndef ENEMY_SMB_BOWSER_H
#define ENEMY_SMB_BOWSER_H

#include "../enemy.h"

class Bowser : public Enemy
{
public:
    Bowser(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate() override;
    virtual void onSideHit(bool left) override;
    virtual void onFloorHit() override;
    virtual bool onPlayerHeadBump() override;
    virtual void onDeath() override;
    
    virtual void kill() override;
private:
    bool can_jump = false;
    int fire_delay = 100;
    sp::Vector2d start_position;
};

#endif//ENEMY_SMB_BOWSER_H

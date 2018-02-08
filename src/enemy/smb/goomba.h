#ifndef GOOMBA_H
#define GOOMBA_H

#include "../enemy.h"

class Goomba : public Enemy
{
public:
    Goomba(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate() override;
    virtual void onSideHit(bool left) override;
    virtual bool onPlayerHeadBump() override;
    
    bool flip;
    enum class State {
        Normal,
        Death
    } state;
    int state_counter;
};

#endif//GOOMBA_H

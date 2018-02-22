#ifndef ENEMY_SMB_SPINY_H
#define ENEMY_SMB_SPINY_H

#include "../enemy.h"

#include "../enemy.h"
#include <sp2/scene/tilemap.h>

class Spiny : public Enemy
{
public:
    Spiny(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate() override;
    virtual void onSideHit(bool left) override;
    virtual bool onPlayerHeadBump() override;
private:
    bool flip;
};

#endif//ENEMY_SMB_LAKITU_H

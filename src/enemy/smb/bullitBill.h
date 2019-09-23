#ifndef ENEMY_SMB_BULLIT_BILL_H
#define ENEMY_SMB_BULLIT_BILL_H

#include "../enemy.h"

class BullitBill : public Enemy
{
public:
    BullitBill(sp::P<sp::Node> parent, float x, float y);

    virtual void onEnemyUpdate() override;
    virtual void onSideHit(bool left) override;
    virtual bool onPlayerHeadBump() override;

private:
};

class BullitGenerator : public sp::Node
{
public:
    BullitGenerator(sp::P<sp::Node> parent, float x, float y);

    virtual void onUpdate(float delta) override;
private:
    float x, y;
    float spawn_delay;
};

#endif//ENEMY_SMB_BULLIT_BILL_H

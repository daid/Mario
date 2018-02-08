#ifndef SMB_KOOPA_H
#define SMB_KOOPA_H

#include "../enemy.h"
#include <sp2/scene/tilemap.h>

class Koopa : public Enemy
{
public:
    enum class Type
    {
        Green,
        Red,
        ParatroopaRed,
        ParatroopaGreen
    };
    enum class Behaviour
    {
        Walking,
        WalkingNoEdge,
        Leaping,
        FlyingUpDown,
        FlyingLeftRight
    };
    
    Koopa(sp::P<sp::Node> parent, float x, float y, Type type=Type::Green, Behaviour behaviour=Behaviour::Walking);

    virtual void onEnemyUpdate() override;
    virtual void onCollision(sp::CollisionInfo& info) override;
    virtual void onSideHit(bool left) override;
    virtual void onFloorHit() override;
    virtual bool onPlayerHeadBump() override;
    virtual bool onPlayerSideBump(bool left) override;

private:
    bool flip;

    Type type;
    Behaviour behaviour;
    enum class State
    {
        Normal,
        Down,
        Skating
    } state;
    sp::Vector2d start_position;
};

#endif//GOOMBA_H

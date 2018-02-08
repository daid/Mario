#ifndef PICKUP_H
#define PICKUP_H

#include <sp2/scene/node.h>

class PlayerPawn;
class Pickup : public sp::Node
{
public:
    enum class Movement
    {
        Still,
        Slide,
        Bounce
    };
    
    Pickup(sp::P<sp::Node> parent, Movement movement);

    virtual void onFixedUpdate() override;
    virtual void onCollision(sp::CollisionInfo& info) override;

    virtual bool onPickup(sp::P<PlayerPawn> player) = 0;
private:
    enum class State
    {
        Rise,
        Move
    } state = State::Rise;
    Movement movement;
    double rise_level = 0.0;
    bool flip = false;
};

#endif//PICKUP_H

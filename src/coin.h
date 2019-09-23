#ifndef COIN_H
#define COIN_H

#include <sp2/scene/node.h>

class Coin : public sp::Node
{
public:
    Coin(sp::P<sp::Node> parent);

    virtual void onCollision(sp::CollisionInfo& info) override;
};

#endif//COIN_H

#ifndef FLAG_POLE_H
#define FLAG_POLE_H

#include <sp2/scene/node.h>

class Flagpole : public sp::Node
{
public:
    Flagpole(sp::P<sp::Node> parent, double x);

    virtual void onCollision(sp::CollisionInfo& info) override;
};

#endif//FLAG_POLE_H

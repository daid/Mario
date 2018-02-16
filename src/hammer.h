#ifndef HAMMER_H
#define HAMMER_H

#include <sp2/scene/node.h>

class Hammer : public sp::Node
{
public:
    Hammer(sp::P<sp::Node> parent, double x, double y);

    virtual void onUpdate(float delta) override;
    virtual void onCollision(sp::CollisionInfo& info) override;
};

#endif//HAMMER_H

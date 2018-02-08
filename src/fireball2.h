#ifndef FIREBALL2_H
#define FIREBALL2_H

#include <sp2/scene/node.h>

class Fireball2 : public sp::Node
{
public:
    Fireball2(sp::P<sp::Node> parent, double target_y);

    virtual void onFixedUpdate() override;
    virtual void onCollision(sp::CollisionInfo& info) override;

private:
    double target_y;
};

#endif//FIREBALL2_H

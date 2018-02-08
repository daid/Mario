#ifndef FIREBALL_H
#define FIREBALL_H

#include <sp2/scene/node.h>

class Fireball : public sp::Node
{
public:
    Fireball(sp::P<sp::Node> parent, bool left);

    virtual void onFixedUpdate() override;
    virtual void onCollision(sp::CollisionInfo& info) override;
private:
    bool left;
};

#endif//FIREBALL_H

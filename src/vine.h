#ifndef VINE_H
#define VINE_H

#include <sp2/scene/node.h>

class Vine : public sp::Node
{
public:
    Vine(sp::P<sp::Node> parent);

    virtual void onFixedUpdate() override;
private:
    float size;
};

#endif//TRAMPOLINE_H

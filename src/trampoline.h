#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H

#include <sp2/scene/node.h>
#include <sp2/scene/tilemap.h>

class Trampoline : public sp::Node
{
public:
    Trampoline(sp::P<sp::Node> parent);

    virtual void onUpdate(float delta) override;
private:
};

#endif//TRAMPOLINE_H

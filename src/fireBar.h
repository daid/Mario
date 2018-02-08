#ifndef FIREBAR_H
#define FIREBAR_H

#include <sp2/scene/node.h>

class FireBar : public sp::Node
{
public:
    enum class Type
    {
        Left,
        Right,
        RightFast
    };
    enum class Size
    {
        Default,
        Long
    };
    FireBar(sp::P<sp::Node> parent, Type type, Size size=Size::Default);
    
    virtual void onFixedUpdate() override;
    virtual void onCollision(sp::CollisionInfo& info) override;
private:
    Type type;
};

#endif//LIFT_H

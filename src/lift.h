#ifndef LIFT_H
#define LIFT_H

#include <sp2/scene/node.h>

class Lift : public sp::Node
{
public:
    enum class Type
    {
        Up,
        Down,
        UpDown,
        LeftRight,
        Fall,
        Surfing,
        Balance
    };
    enum class Size
    {
        Default,
        Small,
        Tiny
    };
    Lift(sp::P<sp::Node> parent, Type type, Size size=Size::Default);
    
    virtual void onFixedUpdate() override;
    void link(Lift* other) { this->other = other; }
private:
    Type type;
    sp::Vector2d start_position;
    sp::Vector2d size;
    
    sp::P<Lift> other;
};

#endif//LIFT_H

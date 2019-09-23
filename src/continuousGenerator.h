#ifndef CONTINUOUS_GENERATOR_H
#define CONTINUOUS_GENERATOR_H

#include <sp2/scene/node.h>

class ContinuousGenerator : public sp::Node
{
public:
    enum class Type
    {
        BowserFire,
        Bullit,
        CheepCheepJump,
        CheepCheepSwim
    };

    ContinuousGenerator(sp::P<sp::Node> parent, Type type, double start_x);
    void setEndX(double x);

    virtual void onUpdate(float delta) override;

private:
    double start_x;
    double end_x;
    Type type;
    float delay = 0;
};

#endif//CONTINUOUS_GENERATOR_H

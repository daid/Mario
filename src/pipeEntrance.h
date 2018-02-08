#ifndef PIPE_ENTRANCE_H
#define PIPE_ENTRANCE_H

#include <sp2/scene/node.h>

class PipeEntrance : public sp::Node
{
public:
    enum class Type
    {
        Top,
        Left
    };

    PipeEntrance(sp::P<sp::Node> parent, Type type, std::function<void()> func);
    
    virtual void onCollision(sp::CollisionInfo& info) override;

    std::function<void()> func;

    static sp::P<PipeEntrance> active_entrance;
private:
    Type type;
};

#endif//PIPE_ENTRANCE_H

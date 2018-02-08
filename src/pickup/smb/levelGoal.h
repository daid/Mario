#ifndef PICKUP_SMB_LEVEL_GOAL_H
#define PICKUP_SMB_LEVEL_GOAL_H

#include "../pickup.h"

class LevelGoalPickup : public sp::Node
{
public:
    enum class Type
    {
        Toad,
        Princess
    };
    LevelGoalPickup(sp::P<sp::Node> parent, Type type);
    
    virtual void onCollision(sp::CollisionInfo& info) override;
private:
};


#endif//PICKUP_SMB_LEVEL_GOAL_H

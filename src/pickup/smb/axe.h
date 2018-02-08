#ifndef PICKUP_SMB_AXE_H
#define PICKUP_SMB_AXE_H

#include "../pickup.h"
#include <sp2/scene/tilemap.h>

class AxePickup : public sp::Node
{
public:
    AxePickup(sp::P<sp::Tilemap> tilemap);
    
    virtual void onFixedUpdate() override;
    virtual void onCollision(sp::CollisionInfo& info) override;
private:
    bool triggered = false;
    int delay = 10;
    int remove_x;
    sp::P<sp::Tilemap> tilemap;
};


#endif//PICKUP_SMB_AXE_H

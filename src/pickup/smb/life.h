#ifndef PICKUP_SMB_LIFE_H
#define PICKUP_SMB_LIFE_H

#include "../pickup.h"

class LifePickup : public Pickup
{
public:
    LifePickup(sp::P<sp::Node> parent);
    
    virtual bool onPickup(sp::P<PlayerPawn> player);
private:
};


#endif//PICKUP_SMB_LIFE_H

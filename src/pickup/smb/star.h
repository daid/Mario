#ifndef PICKUP_SMB_STAR_H
#define PICKUP_SMB_STAR_H

#include "../pickup.h"

class StarPickup : public Pickup
{
public:
    StarPickup(sp::P<sp::Node> parent);
    
    virtual bool onPickup(sp::P<PlayerPawn> player) override;
private:
};


#endif//PICKUP_SMB_UPGRADE_H

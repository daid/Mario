#ifndef PICKUP_SMB_UPGRADE_H
#define PICKUP_SMB_UPGRADE_H

#include "../pickup.h"

class UpgradePickup : public Pickup
{
public:
    enum class Type
    {
        Mushroom,
        Flower
    };
    
    UpgradePickup(sp::P<sp::Node> parent, Type type);
    
    virtual bool onPickup(sp::P<PlayerPawn> player);
private:
};


#endif//PICKUP_SMB_UPGRADE_H

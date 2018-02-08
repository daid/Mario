#include "continuousGenerator.h"
#include "fireball2.h"
#include "enemy/smb/cheepCheep.h"
#include "enemy/smb/cheepCheepJump.h"
#include "enemy/smb/bullitBill.h"

#include <sp2/random.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>

ContinuousGenerator::ContinuousGenerator(sp::P<sp::Node> parent, Type type, double start_x)
: sp::Node(parent), start_x(start_x), type(type)
{
    end_x = std::numeric_limits<double>::max();
}

void ContinuousGenerator::setEndX(double x)
{
    end_x = std::min(end_x, x);
}

void ContinuousGenerator::onUpdate(float delta)
{
    sp::Vector2d camera_position = getScene()->getCamera()->getPosition2D();
    if (camera_position.x + 8 < start_x || camera_position.x + 8 >= end_x)
        return;
    
    if (delay > 0)
    {
        delay -= delta;
        return;
    }
    delay = 3.0;
    switch(type)
    {
    case Type::BowserFire:
        (new Fireball2(getParent(), -1))->setPosition(sp::Vector2d(camera_position.x + 9.5, sp::random(5, 8)));
        break;
    case Type::Bullit:
        new BullitBill(getParent(), camera_position.x + 9.0, sp::random(2.0, 10.0));
        break;
    case Type::CheepCheepJump:
        new CheepCheepJump(getParent(), camera_position.x + sp::random(-6, 10), -1);
        delay = 1.0;
        break;
    case Type::CheepCheepSwim:
        new CheepCheep(getParent(), camera_position.x + 9.0, sp::random(2.0, 10.0));
        delay = 2.0;
        break;
    }
}

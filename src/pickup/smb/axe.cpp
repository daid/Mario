#include "axe.h"

#include "../../playerPawn.h"

#include <sp2/engine.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/camera.h>
#include <sp2/audio/sound.h>
#include <sp2/collision/2d/circle.h>
#include <sp2/graphics/spriteAnimation.h>


AxePickup::AxePickup(sp::P<sp::Tilemap> tilemap)
: sp::Node(tilemap->getParent()), tilemap(tilemap)
{
    sp::collision::Circle2D shape(0.5);
    shape.type = sp::collision::Shape::Type::Sensor;
    shape.fixed_rotation = true;
    setCollisionShape(shape);

    setAnimation(sp::SpriteAnimation::load("upgrade.txt"));
    animationPlay("Axe");
    
    render_data.order = -2;
}

void AxePickup::onFixedUpdate()
{
    if (triggered)
    {
        if (delay > 0)
        {
            delay --;
        }
        else
        {
            for(bool did_remove=false; !did_remove; )
            {
                for(int n=0; n<16; n++)
                {
                    if (tilemap->getTileIndex({remove_x, n}) == 113 || tilemap->getTileIndex({remove_x, n}) == 114)
                    {
                        tilemap->setTile({remove_x, n}, -1);
                        did_remove = true;
                    }
                }
                remove_x++;
                if (remove_x > getPosition2D().x)
                {
                    delete this;
                    return;
                }
            }
            sp::audio::Sound::play("sfx/smb_breakblock.wav");
            delay = 10;
        }
    }
}

void AxePickup::onCollision(sp::CollisionInfo& info)
{
    if (bool(info.other) && info.other->isSolid())
    {
        sp::P<PlayerPawn> player = info.other;
        if (player)
        {
            render_data.type = sp::RenderData::Type::None;
            setAnimation(nullptr);
            removeCollisionShape();
            triggered = true;
            
            remove_x = getPosition2D().x - 16;
        }
    }
}

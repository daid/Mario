#include "playerGhost.h"
#include "main.h"

#include <sp2/collision/2d/box.h>
#include <sp2/graphics/spriteAnimation.h>

GhostRecorder::GhostRecorder()
{
    for(auto player : PlayerPawn::all)
    {
        entries.emplace_back();
        auto& e = entries.back();
        e.player = player;
        e.recording.animation_name = player->getAnimationName();
    }
    update();
}

void GhostRecorder::update()
{
    for(auto& entry : entries)
    {
        if (!entry.player)
            continue;
        entry.recording.data.emplace_back();
        auto& e = entry.recording.data.back();
        e.type = PlayerGhostRecording::Entry::Type::Update;
        e.position = entry.player->getPosition2D();
        e.velocity = entry.player->getLinearVelocity2D();
        e.upgrade_level = entry.player->getUpgradeLevel();
        e.state = entry.player->getState();
    }
}

void GhostRecorder::pipeEnterDone()
{
    for(auto& entry : entries)
    {
        if (!entry.player)
            continue;
        entry.recording.data.emplace_back();
        auto& e = entry.recording.data.back();
        e.type = PlayerGhostRecording::Entry::Type::Pipe;
        e.position = entry.player->getPosition2D();
        e.velocity = entry.player->getLinearVelocity2D();
        e.upgrade_level = entry.player->getUpgradeLevel();
        e.state = entry.player->getState();
    }
}

GhostReplay::GhostReplay(sp::P<sp::Node> parent, PlayerGhostRecording& recording, bool solid)
: sp::Node(parent), recording(recording), solid(solid)
{
    setAnimation(sp::SpriteAnimation::load(recording.animation_name));
    animationPlay("Stand");
    render_data.color = sp::Color(1, 1, 1, 0.5);
}

void GhostReplay::pipeEnterDone()
{
    while(index < recording.data.size() && recording.data[index].type != PlayerGhostRecording::Entry::Type::Pipe)
        index++;
    if (index < recording.data.size() && recording.data[index].type == PlayerGhostRecording::Entry::Type::Pipe)
        index++;
    updateCollisionShape();
    render_data.order = 0;
}

void GhostReplay::onFixedUpdate()
{
    if (index == start_collision_index)
        updateCollisionShape();
    if (index < recording.data.size())
    {
        auto& e = recording.data[index];
        switch(e.type)
        {
        case PlayerGhostRecording::Entry::Type::Update:{
            setPosition(e.position);
            setLinearVelocity(e.velocity);
            
            if (e.upgrade_level != last_upgrade_level)
            {
                last_upgrade_level = e.upgrade_level;
                updateCollisionShape();
            }
            
            sp::string animation_prefix = "";
            if (e.upgrade_level == 1)
                animation_prefix = "Large";
            if (e.upgrade_level == 2)
                animation_prefix = "Fire";

            if (e.velocity.x < 0)
                animationSetFlags(sp::SpriteAnimation::FlipFlag);
            if (e.velocity.x > 0)
                animationSetFlags(0);
            switch(e.state)
            {
            case PlayerPawn::State::Death:
                animationPlay("Death");
                break;
            case PlayerPawn::State::Finish:
                if (e.velocity.y != 0.0)
                    animationPlay(animation_prefix + "Climb", 0);
                else if (e.velocity.x != 0.0)
                    animationPlay(animation_prefix + "Walk");
                else
                    animationPlay(animation_prefix + "Stand");
                animationSetFlags(0);
                break;
            case PlayerPawn::State::Swimming:
                animationPlay(animation_prefix + "Swim");
                break;
            case PlayerPawn::State::EnterPipe:
                removeCollisionShape();
                render_data.order = -2;
                //if (PipeEntrance::active_entrance && std::abs(PipeEntrance::active_entrance->getPosition2D().x - getPosition2D().x) > 0.1)
                    animationPlay(animation_prefix + "Walk");
                //else
                //    animationPlay(animation_prefix + "Stand");
                break;
            case PlayerPawn::State::Walking:
                if (e.velocity.x != 0.0)
                    animationPlay(animation_prefix + "Walk");
                else
                    animationPlay(animation_prefix + "Stand");
                break;
            case PlayerPawn::State::Falling:
            case PlayerPawn::State::Jumping:
                animationPlay(animation_prefix + "Jump");
                break;
            }
            index++;
            }break;
        case PlayerGhostRecording::Entry::Type::Pipe:
            break;
        }
    }
    else
    {
        removeCollisionShape();
    }
}

void GhostReplay::updateCollisionShape()
{
    if (index < start_collision_index)
        return;

    if (last_upgrade_level == 0)
    {
        sp::collision::Box2D shape(12.0/16.0, 14.0/16.0, 0, -1.0/16.0);
        shape.type = sp::collision::Shape::Type::Dynamic;
        shape.setFilterCategory(collision_category_ghost);
        shape.setMaskFilterCategory(collision_category_enemy);
        shape.setMaskFilterCategory(collision_category_pickup);
        shape.setMaskFilterCategory(collision_category_ghost);
        if (!solid)
            shape.setMaskFilterCategory(collision_category_player);
        shape.fixed_rotation = true;
        setCollisionShape(shape);
    }else{
        sp::collision::Box2D shape(12.0/16.0, 1.0+12.0/16.0, 0, -2.0/16.0);
        shape.type = sp::collision::Shape::Type::Dynamic;
        shape.setFilterCategory(collision_category_ghost);
        shape.setMaskFilterCategory(collision_category_enemy);
        shape.setMaskFilterCategory(collision_category_pickup);
        shape.setMaskFilterCategory(collision_category_ghost);
        if (!solid)
            shape.setMaskFilterCategory(collision_category_player);
        shape.fixed_rotation = true;
        setCollisionShape(shape);
    }
}

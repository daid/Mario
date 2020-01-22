#ifndef PLAYER_GHOST_H
#define PLAYER_GHOST_H

#include "playerPawn.h"
#include "serializer.h"


class PlayerGhostRecording : public ISerializable
{
public:
    class Entry : public ISerializable
    {
    public:
        enum class Type
        {
            Update,
            Pipe
        } type;
        sp::Vector2d position;
        sp::Vector2d velocity;
        int upgrade_level;
        PlayerPawn::State state;
        
        virtual void serialize(Serializer::Handler& handler) override
        {
            //handler("type", type);
            handler("position", position);
            handler("velocity", velocity);
            handler("upgrade_level", upgrade_level);
            handler("state", state);
        }
    };
    
    sp::string animation_name;
    std::vector<Entry> data;
    
    virtual void serialize(Serializer::Handler& handler) override
    {
        handler("animation_name", animation_name);
        handler("data", data);
    }
};

class GhostRecorder
{
public:
    GhostRecorder();
    
    void update();
    void pipeEnterDone();

    class Entry
    {
    public:
        sp::P<PlayerPawn> player;
        PlayerGhostRecording recording;
    };
    std::vector<Entry> entries;
};

class GhostReplay : public sp::Node
{
public:
    GhostReplay(sp::P<sp::Node> parent, PlayerGhostRecording& recording, bool solid=true);
    
    virtual void onFixedUpdate() override;
    void pipeEnterDone();
private:
    void updateCollisionShape();

    PlayerGhostRecording& recording;
    bool solid;
    unsigned int index = 0;
    int last_upgrade_level = 0;
    static constexpr int start_collision_index = 60;
};

#endif//PLAYER_GHOST_H

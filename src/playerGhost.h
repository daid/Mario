#ifndef PLAYER_GHOST_H
#define PLAYER_GHOST_H

#include "playerPawn.h"


class PlayerGhostRecording
{
public:
    class Entry
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
    };
    
    sp::string animation_name;
    std::vector<Entry> data;
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
};

#endif//PLAYER_GHOST_H

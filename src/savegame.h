#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <sp2/io/serializer.h>
#include <vector>
#include "playerGhost.h"
#include "main.h"

class StageSaveData : public sp::io::ISerializable
{
public:
    static constexpr int required_more_and_more_runs_for_completion = 3;

    bool isLocked();
    bool isVisible();
    bool isFullyCompleted(); //True if we completed this stage with all players alive
    int completedCount();

    int finished = 0;      //maximum amount of players that finished in a single run
    int attempts = 0;      //amount of times this level has been tried
    bool pacifist = false; //finished without a kill
    bool genocide = false; //finished with killing everything
    bool flawless = false; //finished without getting hit
    
    bool is_dirty = false;
    
    double best_time = 400.0;
    
    std::vector<PlayerGhostRecording> best_time_recordings;
    std::vector<PlayerGhostRecording> all_recordings;

    virtual void serialize(sp::io::Serializer::Handler& handler) override;
private:
    StageSaveData* previous = nullptr;
    StageSaveData* world_previous = nullptr;
    
    friend class SaveGame;
};

class SaveGame : public sp::io::ISerializable
{
public:
    static constexpr int world_count = 8;
    static constexpr int stage_count = 4;

    SaveGame();

    StageSaveData& getStage(GameMode mode, int world, int stage);
    int getPlayerCount();
    
    void addCoin();
    int getCoins();
    
    void addLife();
    int getLives();
    
    void load(int player_count);
    void store();

    virtual void serialize(sp::io::Serializer::Handler& handler) override;
private:
    int player_count;
    int coin_count = 0;
    int life_count = 0;
    bool load_stages = false;
    std::vector<StageSaveData> stages;
    std::vector<StageSaveData> world_stages;
};

extern SaveGame save_game;

#endif//SAVEGAME_H

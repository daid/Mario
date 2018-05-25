#include "savegame.h"
#include "main.h"

#include <sp2/logging.h>
#include <json11/json11.hpp>
#include <fstream>

SaveGame save_game;

bool StageSaveData::isLocked()
{
#ifdef DEBUG
    //return false;
#endif
    if (isFullyCompleted())
        return false;
    if (!previous)
        return false;
    if (world_previous)
    {
        if (world_previous->isFullyCompleted())
            return false;
    }
    if (previous->finished >= save_game.getPlayerCount())
        return false;
    if (previous->previous)
    {
        if (previous->finished > 0 && previous->previous->finished >= save_game.getPlayerCount())
            return false;
    }else{
        if (previous->finished > 0)
            return false;
    }
    return true;
}

bool StageSaveData::isVisible()
{
    if (!previous || !previous->isLocked())
        return true;
    if (world_previous && !world_previous->isLocked())
        return true;
    return false;
}

bool StageSaveData::isFullyCompleted()
{
    switch(game_mode)
    {
    case GameMode::Basic:
        return finished >= save_game.getPlayerCount();
    case GameMode::MoreAndMore:
    case GameMode::MoreAndMoreWorld:
        return all_recordings.size() / save_game.getPlayerCount() >= required_more_and_more_runs_for_completion;
    }
    return false;
}

int StageSaveData::completedCount()
{
    switch(game_mode)
    {
    case GameMode::Basic:
        return finished >= save_game.getPlayerCount() ? 1 : 0;
    case GameMode::MoreAndMore:
    case GameMode::MoreAndMoreWorld:
        return all_recordings.size() / save_game.getPlayerCount();
    }
    return 0;
}

SaveGame::SaveGame()
{
    stages.resize(world_count * stage_count);
    for(int w=0; w<world_count; w++)
    {
        for(int s=0; s<stage_count; s++)
        {
            StageSaveData& stage = stages[w * stage_count + s];
            if (w > 0 || s > 0)
                stage.previous = &stages[w * stage_count + s - 1];
            if (w > 0)
                stage.world_previous = &stages[(w - 1) * stage_count + s];
        }
    }
    
    world_stages.resize(world_count);
    for(int w=0; w<world_count; w++)
    {
        StageSaveData& stage = world_stages[w];
        if (w > 0)
            stage.previous = &world_stages[w - 1];
    }
}

StageSaveData& SaveGame::getStage(GameMode mode, int world, int stage)
{
    switch(mode)
    {
    case GameMode::Basic:
    case GameMode::MoreAndMore:
        return stages[world * stage_count + stage];
    case GameMode::MoreAndMoreWorld:
        return world_stages[world];
    }
    return stages[world * stage_count + stage];
}

int SaveGame::getPlayerCount()
{
    return player_count;
}

void SaveGame::addCoin()
{
    coin_count++;
}

int SaveGame::getCoins()
{
    return coin_count;
}

void SaveGame::addLife()
{
    life_count++;
}

int SaveGame::getLives()
{
    return life_count;
}

void SaveGame::load(int player_count)
{
    LOG(Info, "Loading save data for", player_count, "players");

    this->player_count = player_count;

    sp::io::Serializer serializer("save_main.data");
    if (serializer.read("main", *this))
    {
        for(int w=0; w<world_count; w++)
        {
            sp::io::Serializer serializer_world("save_world_" + sp::string(w) + ".data");
            serializer_world.read("stage", getStage(GameMode::MoreAndMoreWorld, w, 0));

            for(int s=0; s<stage_count; s++)
            {
                sp::io::Serializer serializer("save_" + sp::string(w) + "_" + sp::string(s) + ".data");
                serializer.read("stage", getStage(GameMode::MoreAndMore, w, s));
            }
        }
    }
    else
    {
        load_stages = true;
        sp::io::Serializer fallback_serializer("save.data");
        if (!fallback_serializer.read("main", *this))
        {
            std::ifstream file("save.json");
            if (!file.is_open())
                return;
            std::stringstream data;
            data << file.rdbuf();
            sp::string err;

            json11::Json json = json11::Json::parse(data.str(), err);
            if (err != "")
            {
                LOG(Warning, "Failed to load save data:", err);
                return;
            }
            
            for(int w=0; w<world_count; w++)
            {
                for(int s=0; s<stage_count; s++)
                {
                    auto& data = json[sp::string(w) + "-" + sp::string(s)];
                    StageSaveData& save = getStage(GameMode::MoreAndMore, w, s);
                    save.finished = data["finished"].int_value();
                    save.best_time = data["best_time"].number_value();
                    save.attempts = data["attempts"].int_value();
                    save.all_recordings.clear();
                    for(auto& recording_data : data["all_recordings"].array_items())
                    {
                        save.all_recordings.emplace_back();
                        auto& recording = save.all_recordings.back();
                        recording.animation_name = recording_data["animation_name"].string_value();
                        for(auto& e : recording_data["data"].array_items())
                        {
                            recording.data.emplace_back();
                            auto& entry = recording.data.back();
                            entry.type = PlayerGhostRecording::Entry::Type(e["type"].int_value());
                            entry.position.x = e["x"].number_value();
                            entry.position.y = e["y"].number_value();
                            entry.velocity.x = e["vx"].number_value();
                            entry.velocity.y = e["vy"].number_value();
                            entry.upgrade_level = e["u"].int_value();
                            entry.state = PlayerPawn::State(e["state"].int_value());
                            recording.data.emplace_back();
                            auto& entry2 = recording.data.back();
                            entry2 = entry;
                            entry2.position += entry.velocity * 1.0/60.0;
                        }
                    }
                }
            }
            coin_count = json["coins"].int_value();
            life_count = json["lives"].int_value();
        }
        
        load_stages = false;
        for(int w=0; w<world_count; w++)
        {
            for(int s=0; s<stage_count; s++)
            {
                getStage(GameMode::MoreAndMore, w, s).is_dirty = true;
            }
        }
        store();
    }
}

void SaveGame::store()
{
    LOG(Info, "Saving result");

    sp::io::Serializer serializer("save_main.data");
    serializer.write("main", *this);

    for(int w=0; w<world_count; w++)
    {
        if (getStage(GameMode::MoreAndMoreWorld, w, 0).is_dirty)
        {
            sp::io::Serializer serializer("save_world_" + sp::string(w) + ".data");
            serializer.write("stage", getStage(GameMode::MoreAndMoreWorld, w, 0));
        }
        for(int s=0; s<stage_count; s++)
        {
            if (getStage(GameMode::MoreAndMore, w, s).is_dirty)
            {
                sp::io::Serializer serializer("save_" + sp::string(w) + "_" + sp::string(s) + ".data");
                serializer.write("stage", getStage(GameMode::MoreAndMore, w, s));
            }
        }
    }
}

void SaveGame::serialize(sp::io::Serializer::Handler& handler)
{
    if (load_stages)
        handler("stages", stages);
    handler("lives", life_count);
    handler("coins", coin_count);
}

void StageSaveData::serialize(sp::io::Serializer::Handler& handler)
{
    handler("finished", finished);
    handler("attempts", attempts);
    handler("best_time", best_time);
    handler("all_recordings", all_recordings);
}

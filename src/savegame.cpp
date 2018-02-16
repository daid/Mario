#include "savegame.h"
#include "main.h"

#include <sp2/logging.h>
#include <json11/json11.hpp>
#include <fstream>

SaveGame save_game;

bool StageSaveData::isLocked()
{
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
}

StageSaveData& SaveGame::getStage(int world, int stage)
{
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
            StageSaveData& save = getStage(w, s);
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
                }
            }
        }
    }
    coin_count = json["coins"].int_value();
    life_count = json["lives"].int_value();
}

void SaveGame::store()
{
    LOG(Info, "Saving result");

    json11::Json::object obj;
    for(int w=0; w<world_count; w++)
    {
        for(int s=0; s<stage_count; s++)
        {
            StageSaveData& save = getStage(w, s);
            json11::Json::object data;
            data["finished"] = save.finished;
            data["best_time"] = save.best_time;
            data["attempts"] = save.attempts;
            json11::Json::array all_recordings;
            for(auto& recording : save.all_recordings)
            {
                json11::Json::object rec;
                rec["animation_name"] = recording.animation_name.c_str();
                json11::Json::array rec_data;
                for(auto& entry : recording.data)
                {
                    json11::Json::object e;
                    e["type"] = int(entry.type);
                    e["x"] = entry.position.x;
                    e["y"] = entry.position.y;
                    e["vx"] = entry.velocity.x;
                    e["vy"] = entry.velocity.y;
                    e["u"] = entry.upgrade_level;
                    e["state"] = int(entry.state);
                    rec_data.push_back(e);
                }
                rec["data"] = rec_data;
                all_recordings.push_back(rec);
            }
            data["all_recordings"] = all_recordings;
            obj[sp::string(w) + "-" + sp::string(s)] = data;
        }
    }
    obj["coins"] = coin_count;
    obj["lives"] = life_count;
    json11::Json json = obj;
    
    std::ofstream file("save.json");
    file << json.dump();
}

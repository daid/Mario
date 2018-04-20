#ifndef MAIN_H
#define MAIN_H

#include "inputController.h"

#include <sp2/window.h>

class LevelData;
class GlobalAreaData
{
public:
    sp::Vector2d start_position;
    double view_limit;
    double water_level = 12;
    sp::string music_name;
};

enum class GameMode
{
    Basic,
    MoreAndMore
};

extern sp::P<sp::Window> window;

extern GlobalAreaData global_area_data;

extern InputController controller[2];
extern sp::io::Keybinding escape_key;

extern GameMode game_mode;
extern bool return_to_editor;

void loadStage(int world, int stage);
void loadStage(LevelData* level);
void createPlayers(sp::P<sp::Scene> scene);
void destroyPlayers(sp::P<sp::Scene> scene);
bool respawnPlayer();

static constexpr int collision_category_world = 0;
static constexpr int collision_category_player = 1;
static constexpr int collision_category_enemy = 2;
static constexpr int collision_category_pickup = 3;
static constexpr int collision_category_ghost = 4;

#endif//MAIN_H

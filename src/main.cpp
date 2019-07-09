#include <sp2/engine.h>
#include <sp2/window.h>
#include <sp2/logging.h>
#include <sp2/random.h>
#include <sp2/io/directoryResourceProvider.h>
#include <sp2/io/virtualTouchKeys.h>
#include <sp2/audio/music.h>
#include <sp2/graphics/gui/widget/button.h>
#include <sp2/graphics/gui/scene.h>
#include <sp2/graphics/gui/theme.h>
#include <sp2/graphics/gui/loader.h>
#include <sp2/graphics/scene/graphicslayer.h>
#include <sp2/graphics/scene/basicnoderenderpass.h>
#include <sp2/graphics/scene/collisionrenderpass.h>
#include <sp2/graphics/spriteAnimation.h>
#include <sp2/graphics/textureManager.h>
#include <sp2/graphics/textureAtlas.h>
#include <sp2/audio/sound.h>
#include <sp2/scene/scene.h>
#include <sp2/scene/node.h>
#include <sp2/scene/camera.h>
#include <sp2/collision/2d/box.h>
#include <sp2/io/keybinding.h>

#include "smbLevelBuilder.h"
#include "randomLevelGenerator.h"
#include "inputController.h"
#include "playerPawn.h"
#include "camera.h"
#include "savegame.h"
#include "stageSelect.h"
#include "editor.h"
#include "playerGhost.h"
#include "main.h"
#include "coin.h"
#include "flagpole.h"
#include "trampoline.h"

#include "pickup/smb/levelGoal.h"
#include "enemy/smb/goomba.h"
#include "enemy/smb/koopa.h"
#include "enemy/smb/piranhaPlant.h"
#include "enemy/smb/bowser.h"
#include "enemy/smb/blooper.h"
#include "enemy/smb/hammerBrother.h"
#include "enemy/smb/podoboo.h"
#include "enemy/smb/buzzyBeetle.h"
#include "enemy/smb/bullitBill.h"
#include "enemy/smb/lakitu.h"

sp::P<sp::Window> window;

InputController controller[2]{{0}, {1}};
sp::io::Keybinding escape_key{"exit", "Escape"};

GameMode game_mode = GameMode::Random;
bool return_to_editor = false;

GlobalAreaData global_area_data;
std::vector<sp::string> player_animation_names{
    "smb_mario.txt",
    "smb_luigi.txt",
    "smb2_mario.txt",
    "smb2_luigi.txt",
    "smb2_princess.txt",
    "smb2_toad.txt",
    "smb3_mario.txt",
    "smb3_luigi.txt",
};

#include "levels.h"


class StageScene : public sp::Scene
{
public:
    StageScene()
    : sp::Scene("stage")
    {
        gameover = sp::gui::Loader::load("gui/gameover.gui", "GAMEOVER");
        victory = sp::gui::Loader::load("gui/victory.gui", "VICTORY");
        hud = sp::gui::Loader::load("gui/hud.gui", "HUD");

        disable();
    }
    
    void onUpdate(float delta) override
    {
        if (escape_key.getDown())
            handleGameOver(delta);
        
        hud->getWidgetWithID("TIME")->setAttribute("caption", "TIME: " + sp::string(int((max_play_time - play_time) / max_play_time * visible_play_time)));
        hud->getWidgetWithID("COINS")->setAttribute("caption", sp::string(save_game.getCoins()));
        hud->getWidgetWithID("1UP")->setAttribute("caption", sp::string(save_game.getLives()));
        if (play_time >= max_play_time)
        {
            play_time = max_play_time;
            for(auto player : PlayerPawn::all)
                player->takeDamage();
        }
        
        play_time += delta;
        if (PlayerPawn::all.size() < 1)
        {
            handleGameOver(delta);
            return;
        }
        if (PipeEntrance::active_entrance)
        {
            for(auto player : PlayerPawn::all)
            {
                if ((player->getPosition2D() - PipeEntrance::active_entrance->getPosition2D()).length() > 0.01)
                    return;
            }
            recorder->pipeEnterDone();
            auto func = PipeEntrance::active_entrance->func;
            for(auto child : getRoot()->getChildren())
            {
                sp::P<GhostReplay> gr = sp::P<sp::Node>(child);
                if (gr)
                {
                    gr->pipeEnterDone();
                    continue;
                }
                if (!sp::P<PlayerPawn>(sp::P<sp::Node>(child)))
                    child.destroy();
            }
            func();
            for(auto player : PlayerPawn::all)
                player->setPosition(global_area_data.start_position + sp::Vector2d(0.5, 0.5));
            setDefaultCamera(new Camera(getRoot()));
            return;
        }
        for(auto player : PlayerPawn::all)
            if (!player->isFinished())
                return;
        switch(game_mode)
        {
        case GameMode::Basic:
        case GameMode::MoreAndMore:
        case GameMode::Random:
            handleVictory(delta);
            break;
        case GameMode::MoreAndMoreWorld:
            if (active_stage < 3)
            {
                active_stage += 1;
                for(auto child : getRoot()->getChildren())
                {
                    sp::P<GhostReplay> gr = sp::P<sp::Node>(child);
                    if (gr)
                    {
                        continue;
                    }
                    if (!sp::P<PlayerPawn>(child))
                        child.destroy();
                }
                createArea(active_world, active_stage);
                for(auto child : getRoot()->getChildren())
                {
                    sp::P<PlayerPawn> player = sp::P<sp::Node>(child);
                    if (player)
                    {
                        player->setPosition(global_area_data.start_position + sp::Vector2d(0.5, 0.5));
                        player->resetFinished();
                    }
                }
                setDefaultCamera(new Camera(getRoot()));
            }
            else
            {
                handleVictory(delta);
            }
            break;
        }
    }
    
    virtual void onFixedUpdate() override
    {
        if (recorder)
            recorder->update();
    }
    
    virtual void onDisable() override
    {
        gameover->hide();
        victory->hide();
        hud->hide();
        continue_delay = 0;
        if (recorder)
        {
            delete recorder;
            recorder = nullptr;
        }
    }
    
    void loadStage(int world, int stage)
    {
        active_world = world;
        active_stage = stage;
        play_time = 0.0;

        visible_play_time = 400;
        max_play_time = 120;
        if (game_mode == GameMode::MoreAndMoreWorld)
        {
            max_play_time *= 2.5;
            visible_play_time *= 2.5;
        }

        clearAll();
        sp::Scene::get("stage_select")->disable();
        sp::Scene::get("editor")->disable();
        enable();
        hud->show();
        createArea(world, stage);

        createPlayers(this);
        setDefaultCamera(new Camera(getRoot()));
        
        recorder = new GhostRecorder();
        switch(game_mode)
        {
        case GameMode::Basic:
            for(auto& recording : save_game.getStage(game_mode, world, stage).best_time_recordings)
                new GhostReplay(getRoot(), recording, false);
            break;
        case GameMode::MoreAndMore:
        case GameMode::MoreAndMoreWorld:
        case GameMode::Random:
            for(auto& recording : save_game.getStage(game_mode, world, stage).all_recordings)
                new GhostReplay(getRoot(), recording);
            break;
        }
    }

    void loadStage(LevelData* level)
    {
        LOG(Debug, "Loading custom stage");
        active_world = -1;
        active_stage = -1;
        play_time = 0.0;
        
        clearAll();
        sp::Scene::get("stage_select")->disable();
        sp::Scene::get("editor")->disable();
        enable();
        hud->show();

        global_area_data.start_position = sp::Vector2d(2, 13);
        global_area_data.view_limit = level->width;
        global_area_data.music_name = "Overworld";
        global_area_data.water_level = -10;
        sp::audio::Music::play("music/" + global_area_data.music_name + ".ogg");

        sp::P<sp::Tilemap> tilemap = new sp::Tilemap(getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
        for(int x=0; x<level->width; x++)
        {
            for(int y=0; y<level->height; y++)
            {
                int tile = level->getTileIndex(x, y);
                if (tile > -1)
                {
                    tilemap->setTile(x, y, tile, level->isTileSolid(x, y) ? sp::Tilemap::Collision::Solid : sp::Tilemap::Collision::Open);
                    if (tile == 128 || tile == 176)
                        new PiranhaPlant(getRoot(), x + 0.5, y);
                    if (tile == 165)
                        new BullitGenerator(tilemap->getParent(), x, y);
                }
                if (level->tiles[x][y].contents != LevelData::Tile::Contents::None)
                {
                    QuestionBlock::Type type = QuestionBlock::Type::Normal;
                    QuestionBlock::Contents contents = QuestionBlock::Contents::Coin;
                    if (level->tiles[x][y].type == LevelData::Tile::Type::Open) type = QuestionBlock::Type::Hidden;
                    if (level->tiles[x][y].type == LevelData::Tile::Type::Brick) type = QuestionBlock::Type::Brick;
                    if (level->tiles[x][y].type == LevelData::Tile::Type::QuestionBlock) type = QuestionBlock::Type::Normal;
                    switch(level->tiles[x][y].contents)
                    {
                    case LevelData::Tile::Contents::None: break;
                    case LevelData::Tile::Contents::Coin: contents = QuestionBlock::Contents::Coin; break;
                    case LevelData::Tile::Contents::MultiCoin: contents = QuestionBlock::Contents::MultiCoin; break;
                    case LevelData::Tile::Contents::Upgrade: contents = QuestionBlock::Contents::Upgrade; break;
                    case LevelData::Tile::Contents::Star: contents = QuestionBlock::Contents::Star; break;
                    case LevelData::Tile::Contents::Life: contents = QuestionBlock::Contents::Life; break;
                    case LevelData::Tile::Contents::Vine: contents = QuestionBlock::Contents::Vine; break;
                    case LevelData::Tile::Contents::Count: break;
                    }
                    tilemap->setTile(x, y, -1);
                    (new QuestionBlock(tilemap, type, contents))->setPosition(sp::Vector2d(x + 0.5, y + 0.5));
                }
                switch(level->tiles[x][y].type)
                {
                case LevelData::Tile::Type::Open: break;
                case LevelData::Tile::Type::Brick: break;
                case LevelData::Tile::Type::Ground: break;
                case LevelData::Tile::Type::Block: break;
                case LevelData::Tile::Type::Coin: (new Coin(getRoot()))->setPosition(sp::Vector2d(x + 0.5, y + 0.5)); break;
                case LevelData::Tile::Type::QuestionBlock: break;
                case LevelData::Tile::Type::Pipe: break;
                case LevelData::Tile::Type::PipeRed: break;
                case LevelData::Tile::Type::Island: break;
                case LevelData::Tile::Type::MushroomIsland: break;
                case LevelData::Tile::Type::Trampoline: (new Trampoline(getRoot()))->setPosition(sp::Vector2d(x + 0.5, y + 1.0)); break;
                case LevelData::Tile::Type::BullitTower: break;
                case LevelData::Tile::Type::FirebarLeft: (new FireBar(getRoot(), FireBar::Type::Left))->setPosition(sp::Vector2d(x + 0.5, y + 0.5)); break;
                case LevelData::Tile::Type::FirebarRight: (new FireBar(getRoot(), FireBar::Type::Right))->setPosition(sp::Vector2d(x + 0.5, y + 0.5)); break;
            
                case LevelData::Tile::Type::Goomba: new Goomba(getRoot(), x, y); break;
                case LevelData::Tile::Type::KoopaGreen: new Koopa(getRoot(), x, y); break;
                case LevelData::Tile::Type::KoopaRed: new Koopa(getRoot(), x, y, Koopa::Type::Red, Koopa::Behaviour::WalkingNoEdge); break;
                case LevelData::Tile::Type::KoopaParatrooperGreen: new Koopa(getRoot(), x, y, Koopa::Type::ParatroopaGreen, Koopa::Behaviour::Leaping); break;
                case LevelData::Tile::Type::KoopaParatrooperRed: new Koopa(getRoot(), x, y, Koopa::Type::ParatroopaRed, Koopa::Behaviour::FlyingUpDown); break;
                case LevelData::Tile::Type::Blooper: new Blooper(getRoot(), x, y); break;
                case LevelData::Tile::Type::Podoboo: new Podoboo(getRoot(), x, y); break;
                case LevelData::Tile::Type::HammerBrother: new HammerBrother(getRoot(), x, y); break;
                case LevelData::Tile::Type::Lakitu: new Lakitu(getRoot(), x, y); break;
                case LevelData::Tile::Type::BuzzyBeetle: new BuzzyBeetle(getRoot(), x, y); break;
                case LevelData::Tile::Type::Bowser: new Bowser(getRoot(), x, y); break;
                case LevelData::Tile::Type::Flagpole:
                    for(int n=0; n<7; n++)
                        tilemap->setTile(x, y + n, 30);
                    tilemap->setTile(x, y + 7, 14);
                    (new Flagpole(getRoot(), x + 0.5))->setPosition(sp::Vector2d(x + 0.5, y));
                    break;
                case LevelData::Tile::Type::Princess: (new LevelGoalPickup(getRoot(), LevelGoalPickup::Type::Princess))->setPosition(sp::Vector2d(x + 0.5, y + 0.5)); break;

                case LevelData::Tile::Type::Count: break;
                }
            }
        }

        createPlayers(this);
        setDefaultCamera(new Camera(getRoot()));
    }

private:
    void clearAll()
    {
        for(auto child : getRoot()->getChildren())
            child.destroy();
    }

    void createArea(int world, int stage)
    {
        if (game_mode == GameMode::Random)
        {
            RandomLevelGenerator generator;
            generator.generate(this, 0x10000 | world << 8 | stage);
            return;
        }
        
        switch(world)
        {
        case 0:
            switch(stage)
            {
            case 0: createArea1_1(this); break;
            case 1: createArea1_2(this); break;
            case 2: createArea1_3(this); break;
            case 3: createArea1_4(this); break;
            }
            break;
        case 1:
            switch(stage)
            {
            case 0: createArea2_1(this); break;
            case 1: createArea2_2(this); break;
            case 2: createArea2_3(this); break;
            case 3: createArea2_4(this); break;
            }
            break;
        case 2:
            switch(stage)
            {
            case 0: createArea3_1(this); break;
            case 1: createArea3_2(this); break;
            case 2: createArea3_3(this); break;
            case 3: createArea3_4(this); break;
            }
            break;
        case 3:
            switch(stage)
            {
            case 0: createArea4_1(this); break;
            case 1: createArea4_2(this); break;
            case 2: createArea4_3(this); break;
            case 3: createArea4_4(this); break;
            }
            break;
        case 4:
            switch(stage)
            {
            case 0: createArea5_1(this); break;
            case 1: createArea5_2(this); break;
            case 2: createArea5_3(this); break;
            case 3: createArea5_4(this); break;
            }
            break;
        case 5:
            switch(stage)
            {
            case 0: createArea6_1(this); break;
            case 1: createArea6_2(this); break;
            case 2: createArea6_3(this); break;
            case 3: createArea6_4(this); break;
            }
            break;
        case 6:
            switch(stage)
            {
            case 0: createArea7_1(this); break;
            case 1: createArea7_2(this); break;
            case 2: createArea7_3(this); break;
            case 3: createArea7_4(this); break;
            }
            break;
        case 7:
            switch(stage)
            {
            case 0: createArea8_1(this); break;
            case 1: createArea8_2(this); break;
            case 2: createArea8_3(this); break;
            case 3: createArea8_4(this); break;
            }
            break;
        }
    }
    
    void handleGameOver(float delta)
    {
        if (continue_delay == 0.0)
        {
            clearAll();
            sp::audio::Music::stop();
            window->setClearColor(sp::Color(0, 0, 0));
            gameover->show();
            hud->hide();
            continue_delay = 3.0;

            if (active_world > -1)
            {
                StageSaveData& save = save_game.getStage(game_mode, active_world, active_stage);
                save.attempts++;
                save.is_dirty = true;
                save_game.store();
            }
        }
        else
        {
            continue_delay -= delta;
            if (continue_delay <= 0.0)
            {
                disable();
                if (return_to_editor)
                    sp::Scene::get("editor")->enable();
                else
                    sp::Scene::get("stage_select")->enable();
            }
        }
    }

    void handleVictory(float delta)
    {
        if (continue_delay == 0.0)
        {
            hud->hide();
            victory->show();
            victory->getWidgetWithID("MISSING_BROTHER")->setVisible(PlayerPawn::all.size() < save_game.getPlayerCount());
            victory->getWidgetWithID("NO_PRINCESS")->setVisible(active_stage >= 3 && active_world < 7);
            sp::audio::Music::stop();
            if (active_stage < 3)
            {
                sp::audio::Sound::play("sfx/smb_stage_clear.wav");
                continue_delay = 5.0;
            }
            else
            {
                sp::audio::Sound::play("sfx/smb_world_clear.wav");
                continue_delay = 6.0;
            }
            
            if (active_world > -1)
            {
                StageSaveData& save = save_game.getStage(game_mode, active_world, active_stage);
                save.finished = std::max(save.finished, PlayerPawn::all.size());
                save.attempts++;
                if (PlayerPawn::all.size() == save_game.getPlayerCount())
                {
                    switch(game_mode)
                    {
                    case GameMode::Basic:
                        if (save.best_time > play_time)
                        {
                            save.best_time = play_time;
                            save.best_time_recordings.clear();
                            for(auto& e : recorder->entries)
                                save.best_time_recordings.push_back(e.recording);
                        }
                        break;
                    case GameMode::MoreAndMore:
                    case GameMode::MoreAndMoreWorld:
                    case GameMode::Random:
                        for(auto& e : recorder->entries)
                            save.all_recordings.push_back(e.recording);
                        break;
                    }
                }
                save.is_dirty = true;
                save_game.store();
            }
        }
        else
        {
            continue_delay -= delta;
            if (continue_delay <= 0.0)
            {
                clearAll();
                disable();
                if (return_to_editor)
                    sp::Scene::get("editor")->enable();
                else
                    sp::Scene::get("stage_select")->enable();
            }
        }
    }

    sp::P<sp::gui::Widget> gameover;
    sp::P<sp::gui::Widget> victory;
    sp::P<sp::gui::Widget> hud;
    float continue_delay;
    float play_time;
    int active_world;
    int active_stage;
    GhostRecorder* recorder = nullptr;
    
    float visible_play_time = 400;
    float max_play_time = 120;
};

void loadStage(int world, int stage)
{
    (sp::P<StageScene>(sp::Scene::get("stage")))->loadStage(world, stage);
}

void loadStage(LevelData* level)
{
    (sp::P<StageScene>(sp::Scene::get("stage")))->loadStage(level);
}

void createPlayers(sp::P<sp::Scene> scene)
{
    std::vector<sp::string> names = player_animation_names;
    for(int n=0; n<save_game.getPlayerCount(); n++)
    {
        int index = sp::irandom(0, names.size() -1);
        sp::string animation_name = names[index];
        names.erase(names.begin() + index);
        sp::P<PlayerPawn> player = new PlayerPawn(scene->getRoot(), controller[n], animation_name);
        player->setPosition(global_area_data.start_position + sp::Vector2d(0.5, 0.5));
    }
}

bool respawnPlayer()
{
    for(int n=0; n<save_game.getPlayerCount(); n++)
    {
        bool player_alive = false;
        for(auto player : PlayerPawn::all)
        {
            if (&player->controller == &controller[n])
                player_alive = true;
        }
        if (!player_alive)
        {
            for(auto player : PlayerPawn::all)
            {
                if (player->getState() != PlayerPawn::State::Death)
                {
                    sp::P<PlayerPawn> new_player = new PlayerPawn(player->getParent(), controller[n], player_animation_names[sp::irandom(0, player_animation_names.size() -1)]);
                    new_player->setPosition(player->getPosition2D() + sp::Vector2d(0, 1));
                    return true;
                }
            }
        }
    }
    return false;
}

void destroyPlayers(sp::P<sp::Scene> scene)
{
    for(auto child : scene->getRoot()->getChildren())
    {
        sp::P<PlayerPawn> player = sp::P<sp::Node>(child);
        player.destroy();
    }
}

int main(int argc, char** argv)
{
    sp::P<sp::Engine> engine = new sp::Engine();

    //Create resource providers, so we can load things.
    new sp::io::DirectoryResourceProvider("resources");

#ifndef DEBUG
    sp::texture_manager.setFallbackColors(sp::Color(0,0,0,0), sp::Color(0,0,0,0));
#endif
    sp::texture_manager.setDefaultSmoothFiltering(false);
    sp::SpriteAnimation::setAtlasManager(new sp::AtlasManager(sp::Vector2i(1024, 1024)));

    //Create a window to render on, and our engine.
    window = new sp::Window(4.0/3.0);
#ifndef DEBUG
    window->setFullScreen(true);
    window->hideCursor();
#endif
    
    sp::gui::Theme::loadTheme("default", "gui/theme/basic.theme.txt");
    new sp::gui::Scene(sp::Vector2d(256, 192), sp::gui::Scene::Direction::Vertical);

    sp::P<sp::SceneGraphicsLayer> scene_layer = new sp::SceneGraphicsLayer(1);
    scene_layer->addRenderPass(new sp::BasicNodeRenderPass());
#ifdef DEBUG
    scene_layer->addRenderPass(new sp::CollisionRenderPass());
#endif
    window->addLayer(scene_layer);

#ifdef ANDROID
    save_game.load(1);
#else
    save_game.load(2);
#endif
    new StageScene();
    new EditorScene();
    new StageSelectScene();
    //new MarkovChainLearningScene();
    
#ifdef DEBUG
    //sp::Scene::get("stage_select")->disable();
    //sp::Scene::get("editor")->enable();
#endif

#ifdef ANDROID
    sp::io::VirtualTouchKeyLayer* touch_layer = new sp::io::VirtualTouchKeyLayer(50);
    touch_layer->addButton(sp::Rect2f(sp::Vector2f(0, 0), sp::Vector2f(0.15, 0.5)), controller[0].running);
    touch_layer->addButton(sp::Rect2f(sp::Vector2f(0.15, 0), sp::Vector2f(0.15, 0.5)), controller[0].running);
    controller[0].left.addKey(controller[0].running.getKey(1));
    controller[0].right.addKey(controller[0].running.getKey(2));
    touch_layer->addButton(sp::Rect2f(sp::Vector2f(0, 0.5), sp::Vector2f(0.15, 0.5)), controller[0].left);
    touch_layer->addButton(sp::Rect2f(sp::Vector2f(0.15, 0.5), sp::Vector2f(0.15, 0.5)), controller[0].right);
    touch_layer->addButton(sp::Rect2f(sp::Vector2f(0.70, 0), sp::Vector2f(0.30, 1.0)), controller[0].jump);
    window->addLayer(touch_layer);
    
    escape_key.addKey("AC Back");
#else
    sp::io::Keybinding::loadKeybindings("keys.txt");
#endif
    engine->run();
#ifndef ANDROID
    sp::io::Keybinding::saveKeybindings("keys.txt");
#endif
    
    return 0;
}

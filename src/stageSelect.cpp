#include "stageSelect.h"
#include "camera.h"
#include "smbLevelBuilder.h"
#include "savegame.h"
#include "playerPawn.h"
#include "main.h"

#include <sp2/scene/tilemap.h>
#include <sp2/graphics/gui/loader.h>
#include <sp2/graphics/gui/widget/button.h>
#include <sp2/graphics/fontManager.h>
#include <sp2/audio/music.h>
#include <sp2/window.h>
#include <sp2/random.h>
#include <sp2/engine.h>

StageSelectScene::StageSelectScene()
: sp::Scene("stage_select")
{
    {
        setDefaultCamera(new Camera(getRoot()));
    }

    {
        gui = sp::gui::Loader::load("gui/level_select.gui", "LEVEL_SELECT");
        selection = gui->getWidgetWithID("STAGE_" + sp::string(world_index + 1) + "-" + sp::string(stage_index + 1));
        indicator = gui->getWidgetWithID("INDICATOR");

        for(int w=0; w<SaveGame::world_count; w++)
        {
            for(int s=0; s<SaveGame::stage_count; s++)
            {
                sp::P<sp::gui::Widget> button = gui->getWidgetWithID("STAGE_" + sp::string(w + 1) + "-" + sp::string(s + 1));
                button->setEventCallback([this, w, s](sp::Variant v)
                {
                    chooseStage(w, s);
                });
            }
        }
    }

    onEnable();
}

void StageSelectScene::onEnable()
{
    gui->show();

    buildBackgroundLevel();
    sp::Window::getInstance()->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    sp::audio::Music::stop();

    createPlayers(this);

    for(int w=0; w<SaveGame::world_count; w++)
    {
        for(int s=0; s<SaveGame::stage_count; s++)
        {
            StageSaveData& save = save_game.getStage(w, s);
            sp::P<sp::gui::Widget> button = gui->getWidgetWithID("STAGE_" + sp::string(w + 1) + "-" + sp::string(s + 1));
            button->setVisible(save.isVisible());
            if (save.isLocked())
                button->disable();
            else
                button->enable();
            button->getWidgetWithID("LOCK")->setVisible(save.isLocked());
            for(int n=1; button->getWidgetWithID("CHECK" + sp::string(n)); n++)
                button->getWidgetWithID("CHECK" + sp::string(n))->setVisible(save.completedCount() >= n);
        }
    }
    
    changeSelection(sp::Vector2d(-1, -1));
}

void StageSelectScene::onDisable()
{
    gui->hide();
    destroyPlayers(this);
}

void StageSelectScene::onUpdate(float delta)
{
    indicator->setParent(selection);
    if (controller[0].right.getDown())
        changeSelection(sp::Vector2d(selection->getGlobalPosition2D()) + sp::Vector2d(selection->getRenderSize().x * 1.5, selection->getRenderSize().y / 2));
    if (controller[0].left.getDown())
        changeSelection(sp::Vector2d(selection->getGlobalPosition2D()) + sp::Vector2d(-selection->getRenderSize().x * 0.5, selection->getRenderSize().y / 2));
    if (controller[0].up.getDown())
        changeSelection(sp::Vector2d(selection->getGlobalPosition2D()) + sp::Vector2d(selection->getRenderSize().x * 0.5, selection->getRenderSize().y * 1.5));
    if (controller[0].down.getDown())
        changeSelection(sp::Vector2d(selection->getGlobalPosition2D()) + sp::Vector2d(selection->getRenderSize().x * 0.5, -selection->getRenderSize().y * 0.5));
    if (controller[0].running.getDown() && selection->isEnabled())
        selection->onPointerUp(sp::Vector2d(1, 1), -1);

    if (escape_key.getDown())
        sp::Engine::getInstance()->shutdown();
    
    switch(secret_code)
    {
    case 0:
        if (controller[1].up.getDown())
            secret_code = 1;
        break;
    case 1:
        if (controller[1].up.getDown())
            secret_code++;
        else if (controller[1].up.getDown() || controller[1].down.getDown() || controller[1].left.getDown() || controller[1].right.getDown() || controller[1].jump.getDown() || controller[1].running.getDown())
            secret_code = 0;
        break;
    case 2:
        if (controller[1].down.getDown())
            secret_code++;
        else if (controller[1].up.getDown() || controller[1].down.getDown() || controller[1].left.getDown() || controller[1].right.getDown() || controller[1].jump.getDown() || controller[1].running.getDown())
            secret_code = 0;
        break;
    case 3:
        if (controller[1].down.getDown())
            secret_code++;
        else if (controller[1].up.getDown() || controller[1].down.getDown() || controller[1].left.getDown() || controller[1].right.getDown() || controller[1].jump.getDown() || controller[1].running.getDown())
            secret_code = 0;
        break;
    case 4:
        if (controller[1].left.getDown())
            secret_code++;
        else if (controller[1].up.getDown() || controller[1].down.getDown() || controller[1].left.getDown() || controller[1].right.getDown() || controller[1].jump.getDown() || controller[1].running.getDown())
            secret_code = 0;
        break;
    case 5:
        if (controller[1].right.getDown())
            secret_code++;
        else if (controller[1].up.getDown() || controller[1].down.getDown() || controller[1].left.getDown() || controller[1].right.getDown() || controller[1].jump.getDown() || controller[1].running.getDown())
            secret_code = 0;
        break;
    case 6:
        if (controller[1].left.getDown())
            secret_code++;
        else if (controller[1].up.getDown() || controller[1].down.getDown() || controller[1].left.getDown() || controller[1].right.getDown() || controller[1].jump.getDown() || controller[1].running.getDown())
            secret_code = 0;
        break;
    case 7:
        if (controller[1].right.getDown())
            secret_code++;
        else if (controller[1].up.getDown() || controller[1].down.getDown() || controller[1].left.getDown() || controller[1].right.getDown() || controller[1].jump.getDown() || controller[1].running.getDown())
            secret_code = 0;
        break;
    case 8:
        if (controller[1].running.getDown())
            secret_code++;
        else if (controller[1].up.getDown() || controller[1].down.getDown() || controller[1].left.getDown() || controller[1].right.getDown() || controller[1].jump.getDown() || controller[1].running.getDown())
            secret_code = 0;
        break;
    case 9:
        if (controller[1].jump.getDown())
            secret_code++;
        else if (controller[1].up.getDown() || controller[1].down.getDown() || controller[1].left.getDown() || controller[1].right.getDown() || controller[1].jump.getDown() || controller[1].running.getDown())
            secret_code = 0;
        break;
    }
}

void StageSelectScene::changeSelection(sp::Vector2d position)
{
    sp::P<sp::gui::Widget> new_selection = gui->getWidgetAt<sp::gui::Button>(position);
    if (new_selection)
        selection = new_selection;
    
    sp::Vector2i world_stage = sp::stringutil::convert::toVector2i(selection->tag) - sp::Vector2i(1, 1);
    StageSaveData& save = save_game.getStage(world_stage.x, world_stage.y);

    gui->getWidgetWithID("STAGE_LOCKED")->setVisible(save.isLocked());
    if (save.isLocked())
    {
        sp::string unlock_info = "LOCKED\n\nFinish:\n";
        if (world_stage.y > 0)
            unlock_info += sp::string(world_stage.x + 1) + "-" + sp::string(world_stage.y);
        else
            unlock_info += sp::string(world_stage.x) + "-" + sp::string(SaveGame::stage_count);
        unlock_info += "\nto unlock";
        if (world_stage.x > 0)
            unlock_info += "\n\n\nFinish:\n" + sp::string(world_stage.x) + "-" + sp::string(world_stage.y + 1) + " x3\nto unlock";
        gui->getWidgetWithID("STAGE_LOCKED")->setAttribute("caption", unlock_info);
        gui->getWidgetWithID("STAGE_INFO_TODO")->hide();
        gui->getWidgetWithID("STAGE_INFO_DONE")->hide();
        gui->getWidgetWithID("STAGE_INFO_TIME")->hide();
        gui->getWidgetWithID("STAGE_INFO_ATTEMPTS")->hide();
        gui->getWidgetWithID("STAGE_INFO_FLAWLESS")->hide();
        gui->getWidgetWithID("STAGE_INFO_PACIFIST")->hide();
        gui->getWidgetWithID("STAGE_INFO_GENOCIDE")->hide();
    }
    else
    {
        gui->getWidgetWithID("STAGE_INFO_TODO")->setVisible(!save.finished);
        gui->getWidgetWithID("STAGE_INFO_DONE")->setVisible(save.finished);
        gui->getWidgetWithID("STAGE_INFO_TIME")->setVisible(save.finished);
        switch(game_mode)
        {
        case GameMode::Basic:
            gui->getWidgetWithID("STAGE_INFO_TIME")->setAttribute("caption", "BEST " + sp::string(save.best_time));
            break;
        case GameMode::MoreAndMore:
            gui->getWidgetWithID("STAGE_INFO_TIME")->setAttribute("caption", "RUNS " + sp::string(save.all_recordings.size() / save_game.getPlayerCount()));
            break;
        }
        gui->getWidgetWithID("STAGE_INFO_ATTEMPTS")->setAttribute("caption", "TRIES " + sp::string(save.attempts));
        gui->getWidgetWithID("STAGE_INFO_ATTEMPTS")->show();
        gui->getWidgetWithID("STAGE_INFO_FLAWLESS")->setVisible(save.flawless);
        gui->getWidgetWithID("STAGE_INFO_PACIFIST")->setVisible(save.pacifist);
        gui->getWidgetWithID("STAGE_INFO_GENOCIDE")->setVisible(save.genocide);
    }
}

void StageSelectScene::chooseStage(int world, int stage)
{
    loadStage(world, stage);
}

void StageSelectScene::buildBackgroundLevel()
{
    for(auto child : getRoot()->getChildren())
        if (child != *getCamera())
            delete child;

    if (sp::random(0, 100) < 10)
    {
        sp::P<sp::Tilemap> tilemap = new sp::Tilemap(getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
        SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Water, SmbLevelBuilder::Scenery::None);
        global_area_data.water_level = 6;
        level.horizontalBlock(1, 4, 3);
        level.horizontalBlock(12, 4, 3);
        level.horizontalBlock(5, 7, 2);
        level.horizontalBlock(9, 7, 2);
        level.nextPage();
    }
    else
    {
        sp::P<sp::Tilemap> tilemap = new sp::Tilemap(getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
        SmbLevelBuilder level(tilemap, SmbLevelBuilder::BaseType::Ground, SmbLevelBuilder::Scenery::Mountain);
        level.horizontalBlock(1, 4, 3);
        level.horizontalBlock(12, 4, 3);
        level.horizontalBlock(5, 7, 2);
        level.horizontalBlock(9, 7, 2);
        level.nextPage();
    }

    global_area_data.view_limit = 0;
    global_area_data.start_position = sp::Vector2d(7.5, 12);
}

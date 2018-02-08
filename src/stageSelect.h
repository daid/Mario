#ifndef STAGE_SELECT_H
#define STAGE_SELECT_H

#include <sp2/scene/scene.h>
#include <sp2/graphics/gui/widget/widget.h>

class StageSelectScene : public sp::Scene
{
public:
    StageSelectScene();
    virtual void onEnable() override;
    virtual void onDisable() override;
    virtual void onUpdate(float delta) override;

private:
    void changeSelection(sp::Vector2d position);
    void chooseStage(int world, int stage);

    int world_index = 0;
    int stage_index = 0;
    sp::P<sp::gui::Widget> gui;
    sp::P<sp::gui::Widget> selection;
    sp::P<sp::gui::Widget> indicator;
};

#endif//STAGE_SELECT_H


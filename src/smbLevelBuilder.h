#ifndef SMB_LEVEL_BUILDER_H
#define SMB_LEVEL_BUILDER_H

#include <sp2/scene/tilemap.h>
#include "enemy/smb/koopa.h"
#include "questionBlock.h"
#include "lift.h"
#include "fireBar.h"


class SmbLevelBuilder
{
public:
    enum class BaseType
    {
        Ground,
        Underground,
        Castle,
        Water
    };
    enum class Scenery
    {
        None,
        Mountain,
        Clouds,
        Fence
    };
    enum class PipeColor
    {
        Green,
        Red,
    };
    static int constexpr AllBricks = 12;
    
    SmbLevelBuilder(sp::P<sp::Tilemap> tilemap, BaseType base_type, Scenery scenery);

    void nextPage();
    void skipToPage(int index);
    void resetPageIndex();
    int getPageIndex();

    void hill(int x, int y, int h);
    void cloud(int x, int y, int w);
    void bushes(int x, int y, int w);
    void tree(int x, int y, int h);
    void fence(int x, int y, int w);
    
    void questionBlock(int x, int y, QuestionBlock::Type type=QuestionBlock::Type::Normal, QuestionBlock::Contents contents=QuestionBlock::Contents::Coin);
    void questionBlockLine(int x, int y, int w, QuestionBlock::Type type=QuestionBlock::Type::Normal, QuestionBlock::Contents contents=QuestionBlock::Contents::Coin);
    void emptyQuestionBlock(int x, int y);
    void coins(int x, int y, int w=1);
    void verticalSeaplant(int x, int y, int h);
    void verticalBricks(int x, int y, int h);
    void horizontalBricks(int x, int y, int w);
    void pipe(int x, int y, int h, PipeColor color=PipeColor::Green);
    void sidePipeEntrance(int x, int y, PipeColor color=PipeColor::Green);
    void hole(int x, int w);
    void holeWithWater(int x, int w);
    void stairs(int x, int y, int size);
    void verticalBlock(int x, int y, int size);
    void horizontalBlock(int x, int y, int size);
    void pole(int x, int y);
    void castle(int x, int y);
    void largeCastle(int x, int y);
    void reverseLPipe(int x, int y, int w=2, int h=2, PipeColor color=PipeColor::Green);
    void island(int x, int y, int w);
    void mushroomIsland(int x, int y, int w);
    void bullitTower(int x, int y, int h);
    void bridge(int x, int y, int w);
    void liftRope(int x);
    void trampoline(int x, int y);

    void castleBridge(int x, int y, int w);
    void bridgeRope(int x, int y);
    void bridgeAxe(int x, int y);

    void setBasic(int x, int surface_size, int ceiling_size=0, int middle_size=0) { basicUpTo(x+1); this->surface_size = surface_size, this->ceiling_size = ceiling_size; this->middle_size = middle_size;}
    void setScrollStop(int x);
    
    void piranhaPlant(int x, int y);
    void toad(int x, int y);
    void princess(int x, int y);
    
    void goomba(int x, int y, int count=1);
    void goomba2(int x, int y);
    void goomba3(int x, int y);
    void koopa(int x, int y, Koopa::Type type=Koopa::Type::Green, Koopa::Behaviour behaviour=Koopa::Behaviour::Walking);
    void koopa2(int x, int y);
    void koopa3(int x, int y);
    void blooper(int x, int y);
    void podoboo(int x, int y);
    void hammerBrother(int x, int y);
    void lakitu(int x, int y);
    void buzzyBeetle(int x, int y);
    void bowser(int x, int y);
    
    void fireBar(int x, int y, FireBar::Type type, FireBar::Size size=FireBar::Size::Default);
    Lift* lift(double x, int y, Lift::Type type, Lift::Size size=Lift::Size::Default);
    void liftBalance(double x1, int y1, double x2, int y2, Lift::Size size=Lift::Size::Default);
    
    void startBowserFire(int x);
    void startBullits(int x);
    void startCheepCheepJumping(int x);
    void startUnderwaterCheepCheeps(int x);
    void stopContinuousGeneration(int x);
    
    void finalize();
private:
    sp::P<sp::Tilemap> tilemap;
    
    void background();
    void basicUpTo(int x);
    void basic(int x);
    
    int last_basic_x;
    int page_index;
    int surface_size, ceiling_size, middle_size;
    BaseType base_type;
    Scenery scenery;
    
    int brick_tile, floor_tile, basic_tile, block_tile;
};

#endif//SMB_LEVEL_BUILDER_H

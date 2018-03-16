#include "smbLevelBuilder.h"

#include "coin.h"
#include "main.h"
#include "flagpole.h"
#include "trampoline.h"
#include "continuousGenerator.h"
#include "pickup/smb/axe.h"
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

#include <sp2/audio/music.h>


SmbLevelBuilder::SmbLevelBuilder(sp::P<sp::Tilemap> tilemap, BaseType base_type, Scenery scenery)
: tilemap(tilemap), base_type(base_type), scenery(scenery)
{
    page_index = 0;
    last_basic_x = 0;
    surface_size = 1;
    ceiling_size = 0;
    middle_size = 0;

    global_area_data.view_limit = std::numeric_limits<double>::max();
    global_area_data.water_level = -10;
    
    switch(base_type)
    {
    case BaseType::Ground:
        global_area_data.music_name = "Overworld";
        brick_tile = 1;
        floor_tile = 0;
        basic_tile = 1;
        block_tile = 16;
        break;
    case BaseType::Underground:
        global_area_data.music_name = "Underground";
        brick_tile = 19;
        floor_tile = 36;
        basic_tile = 19;
        block_tile = 35;
        break;
    case BaseType::Castle:
        global_area_data.music_name = "Castle";
        brick_tile = 99;
        floor_tile = 97;
        block_tile = 97;
        basic_tile = 97;
        break;
    case BaseType::Water:
        global_area_data.music_name = "Underwater";
        brick_tile = 20;
        floor_tile = 20;
        block_tile = 20;
        basic_tile = 20;
        global_area_data.water_level = 12;
        break;
    }
    sp::audio::Music::play("music/" + global_area_data.music_name + ".ogg");
}

void SmbLevelBuilder::nextPage()
{
    basicUpTo(16);
    background();
    page_index++;
}

void SmbLevelBuilder::skipToPage(int index)
{
    while(page_index < index)
        nextPage();
}

void SmbLevelBuilder::resetPageIndex()
{
    nextPage();
    basicUpTo(16);
    page_index = 0;
}

int SmbLevelBuilder::getPageIndex()
{
    return page_index;
}

void SmbLevelBuilder::hill(int x, int y, int h)
{
    x += page_index * 16;
    for(int n=0; n<h; n++)
    {
        if (tilemap->getTileIndex(x + n, y + n) == -1) tilemap->setTile(x + n, y + n, 32);
        if (tilemap->getTileIndex(x + h * 2 - n, y + n) == -1) tilemap->setTile(x + h * 2 - n, y + n, 34);
        for(int m=n+1; m<h*2-n; m++)
            if (tilemap->getTileIndex(x + m, y + n) == -1) tilemap->setTile(x + m, y + n, 48 + ((m - n + 2) % 3));
    }
    if (tilemap->getTileIndex(x + h, y + h) == -1) tilemap->setTile(x + h, y + h, 33);
}

void SmbLevelBuilder::cloud(int x, int y, int w)
{
    x += page_index * 16;

    if (tilemap->getTileIndex(x, y + 1) == -1) tilemap->setTile(x, y + 1, 64);
    if (tilemap->getTileIndex(x, y) == -1) tilemap->setTile(x, y, 80);
    for(int n=1; n<w-1; n++)
    {
        if (tilemap->getTileIndex(x + n, y + 1) == -1) tilemap->setTile(x + n, y + 1, 65);
        if (tilemap->getTileIndex(x + n, y) == -1) tilemap->setTile(x + n, y, 81);
    }
    if (tilemap->getTileIndex(x + w - 1, y + 1) == -1) tilemap->setTile(x + w - 1, y + 1, 66);
    if (tilemap->getTileIndex(x + w - 1, y) == -1) tilemap->setTile(x + w - 1, y, 82);
}

void SmbLevelBuilder::bushes(int x, int y, int w)
{
    x += page_index * 16;

    if (tilemap->getTileIndex(x, y) == -1) tilemap->setTile(x, y, 51);
    for(int n=1; n<w-1; n++)
        if (tilemap->getTileIndex(x + n, y) == -1) tilemap->setTile(x + n, y, 52);
    if (tilemap->getTileIndex(x + w - 1, y) == -1) tilemap->setTile(x + w - 1, y, 53);
}

void SmbLevelBuilder::tree(int x, int y, int h)
{
    x += page_index * 16;

    if (tilemap->getTileIndex(x, y - 1) == -1) return;
    if (tilemap->getTileIndex(x, y) == -1) tilemap->setTile(x, y, 117);
    if (h == 2)
    {
        if (tilemap->getTileIndex(x, y + 1) == -1) tilemap->setTile(x, y + 1, 101);
    }
    else
    {
        if (tilemap->getTileIndex(x, y + 1) == -1) tilemap->setTile(x, y + 1, 118);
        if (tilemap->getTileIndex(x, y + 2) == -1) tilemap->setTile(x, y + 2, 102);
    }
}

void SmbLevelBuilder::fence(int x, int y, int w)
{
    x += page_index * 16;

    for(int n=0; n<w; n++)
        if (tilemap->getTileIndex(x + n, y - 1) != -1 && tilemap->getTileIndex(x + n, y) == -1) tilemap->setTile(x + n, y, 54);
}

void SmbLevelBuilder::questionBlock(int x, int y, QuestionBlock::Type type, QuestionBlock::Contents contents)
{
    basicUpTo(x + 1);
    x += page_index * 16;
    tilemap->setTile(x, y, -1);
    //tilemap->setTile(x, y, 3, sp::Tilemap::Collision::Solid);
    QuestionBlock* qb = new QuestionBlock(tilemap, type, contents);
    qb->setPosition(sp::Vector2d(x + 0.5, y + 0.5));
}

void SmbLevelBuilder::questionBlockLine(int x, int y, int w, QuestionBlock::Type type, QuestionBlock::Contents contents)
{
    for(int n=0; n<w; n++)
        questionBlock(x + n, y, type, contents);
}

void SmbLevelBuilder::emptyQuestionBlock(int x, int y)
{
    basicUpTo(x + 1);
    x += page_index * 16;
    tilemap->setTile(x, y, 3, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::coins(int x, int y, int w)
{
    x += page_index * 16;
    for(int n=0; n<w; n++)
    {
        Coin* coin = new Coin(tilemap->getParent());
        coin->setPosition(sp::Vector2d(x + n + 0.5, y + 0.5));
    }
}

void SmbLevelBuilder::verticalSeaplant(int x, int y, int h)
{
    x += page_index * 16;
    for(int n=0; n<h; n++)
        tilemap->setTile(x, y - n, 4, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::verticalBricks(int x, int y, int h)
{
    x += page_index * 16;
    for(int n=0; n<h; n++)
        tilemap->setTile(x, y - n, brick_tile, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::horizontalBricks(int x, int y, int w)
{
    x += page_index * 16;
    for(int n=0; n<w; n++)
        tilemap->setTile(x + n, y, brick_tile, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::pipe(int x, int y, int h, PipeColor color)
{
    int tile_offset = 0;
    if (color == PipeColor::Red) tile_offset = 32;
    x += page_index * 16;
    if (y < 13)
    {
        tilemap->setTile(x, y, 128 + tile_offset, sp::Tilemap::Collision::Solid);
        tilemap->setTile(x + 1, y, 129 + tile_offset, sp::Tilemap::Collision::Solid);
    }
    for(int n=1; n<h; n++)
    {
        tilemap->setTile(x, y - n, 128 + 16 + tile_offset, sp::Tilemap::Collision::Solid);
        tilemap->setTile(x + 1, y - n, 129 + 16 + tile_offset, sp::Tilemap::Collision::Solid);
    }
}

void SmbLevelBuilder::sidePipeEntrance(int x, int y, PipeColor color)
{
    int tile_offset = 0;
    if (color == PipeColor::Red) tile_offset = 32;
    basicUpTo(x + 1);
    x += page_index * 16;
    tilemap->setTile(x, y, 130 + tile_offset, sp::Tilemap::Collision::Solid);
    tilemap->setTile(x, y - 1, 146 + tile_offset, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::hole(int x, int w)
{
    basicUpTo(x + w);
    x += page_index * 16;
    for(int n=0; n<w; n++)
    {
        for(int m=0; m<5; m++)
            tilemap->setTile(x + n, m, -1);
    }
}

void SmbLevelBuilder::holeWithWater(int x, int w)
{
    hole(x, w);
    x += page_index * 16;
    int tile_upper_water = 67;
    int tile_lower_water = 83;
    if (base_type == BaseType::Castle)
    {
        tile_upper_water++;
        tile_lower_water++;
    }
    for(int n=0; n<w; n++)
    {
        tilemap->setTile(x + n, 2, tile_upper_water);
        tilemap->setTile(x + n, 1, tile_lower_water);
        tilemap->setTile(x + n, 0, tile_lower_water);
    }
}

void SmbLevelBuilder::stairs(int x, int y, int size)
{
    x += page_index * 16;
    for(int n=0; n<size; n++)
    {
        for(int m=0; m<=n; m++)
            tilemap->setTile(x + n, y + m, block_tile, sp::Tilemap::Collision::Solid);
    }
}

void SmbLevelBuilder::verticalBlock(int x, int y, int size)
{
    x += page_index * 16;
    for(int n=0; n<size; n++)
        tilemap->setTile(x, y - n, block_tile, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::horizontalBlock(int x, int y, int size)
{
    x += page_index * 16;
    for(int n=0; n<size; n++)
        tilemap->setTile(x + n, y, block_tile, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::pole(int x, int y)
{
    x += page_index * 16;
    tilemap->setTile(x, y, block_tile, sp::Tilemap::Collision::Solid);
    for(int n=1; n<8; n++)
        tilemap->setTile(x, y + n, 30);
    tilemap->setTile(x, y + 8, 14);
    
    new Flagpole(tilemap->getParent(), x + 0.5);
}

void SmbLevelBuilder::castle(int x, int y)
{
    x += page_index * 16;
    for(int n=0; n<5; n++)
        for(int m=0; m<2; m++)
            tilemap->setTile(x + n, y + m, 2);
    tilemap->setTile(x, y + 2, 11);
    tilemap->setTile(x + 1, y + 2, 27);
    tilemap->setTile(x + 2, y + 2, 27);
    tilemap->setTile(x + 3, y + 2, 27);
    tilemap->setTile(x + 4, y + 2, 11);
    tilemap->setTile(x + 1, y + 3, 12);
    tilemap->setTile(x + 2, y + 3, 2);
    tilemap->setTile(x + 3, y + 3, 13);
    tilemap->setTile(x + 1, y + 4, 11);
    tilemap->setTile(x + 2, y + 4, 11);
    tilemap->setTile(x + 3, y + 4, 11);
    
    tilemap->setTile(x + 2, y, 29);
    tilemap->setTile(x + 2, y + 1, 28);
}

void SmbLevelBuilder::largeCastle(int x, int y)
{
    castle(x + 2, y + 6);
    x += page_index * 16;
    for(int n=0; n<9; n++)
    {
        if (x + n - page_index * 16 < 0)
            continue;
        if (n < 2 || n > 7)
            tilemap->setTile(x + n, y + 5, 11);
        else
            tilemap->setTile(x + n, y + 5, 27);
        for(int m=0; m<5; m++)
            tilemap->setTile(x + n, y + m, 2);
    }
    
    for(int n=2;n<7; n+= 2)
    {
        tilemap->setTile(x + n, y, 29);
        tilemap->setTile(x + n, y + 1, 28);
    }
    for(int n=3;n<6; n+= 2)
    {
        tilemap->setTile(x + n, y + 3, 29);
        tilemap->setTile(x + n, y + 4, 28);
    }
}

void SmbLevelBuilder::castleBridge(int x, int y, int w)
{
    x += page_index * 16;
    for(int n=0; n<w; n++)
        tilemap->setTile(x + n, y, 113, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::bridgeRope(int x, int y)
{
    x += page_index * 16;
    tilemap->setTile(x, y, 114);
}

void SmbLevelBuilder::bridgeAxe(int x, int y)
{
    x += page_index * 16;
    AxePickup* axe = new AxePickup(tilemap);
    axe->setPosition(sp::Vector2d(x + 0.5, y + 0.5));
}

void SmbLevelBuilder::setScrollStop(int x)
{
    x += page_index * 16;
    global_area_data.view_limit = x;
}

void SmbLevelBuilder::piranhaPlant(int x, int y)
{
    x += page_index * 16;
    new PiranhaPlant(tilemap->getParent(), x + 0.5, y);
}

void SmbLevelBuilder::toad(int x, int y)
{
    x += page_index * 16;
    (new LevelGoalPickup(tilemap->getParent(), LevelGoalPickup::Type::Toad))->setPosition(sp::Vector2d(x + 0.5, y + 0.5));
}

void SmbLevelBuilder::princess(int x, int y)
{
    x += page_index * 16;
    (new LevelGoalPickup(tilemap->getParent(), LevelGoalPickup::Type::Princess))->setPosition(sp::Vector2d(x + 0.5, y + 0.5));
}

void SmbLevelBuilder::reverseLPipe(int x, int y, int w, int h, PipeColor color)
{
    int tile_offset = 0;
    if (color == PipeColor::Red) tile_offset = 32;
    basicUpTo(x + w + 2);
    x += page_index * 16;
    tilemap->setTile(x, y + 1, 130 + tile_offset, sp::Tilemap::Collision::Solid);
    tilemap->setTile(x, y, 146 + tile_offset, sp::Tilemap::Collision::Solid);
    for(int n=1; n<w; n++)
    {
        tilemap->setTile(x + n, y + 1, 131 + tile_offset, sp::Tilemap::Collision::Solid);
        tilemap->setTile(x + n, y, 147 + tile_offset, sp::Tilemap::Collision::Solid);
    }
    pipe(x + w - page_index * 16, y + h + 1, h + 2, color);
    tilemap->setTile(x + w, y + 1, 132 + tile_offset, sp::Tilemap::Collision::Solid);
    tilemap->setTile(x + w, y, 148 + tile_offset, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::island(int x, int y, int w)
{
    x += page_index * 16;
    tilemap->setTile(x, y, 133, sp::Tilemap::Collision::Solid);
    for(int n=1; n<w-1; n++)
    {
        tilemap->setTile(x + n, y, 134, sp::Tilemap::Collision::Solid);
        for(int m=0; m<y; m++)
            if (tilemap->getTileIndex(x + n, m) == -1) tilemap->setTile(x + n, m, 18);
    }
    tilemap->setTile(x + w - 1, y, 135, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::mushroomIsland(int x, int y, int w)
{
    x += page_index * 16;
    tilemap->setTile(x, y, 149, sp::Tilemap::Collision::Solid);
    for(int n=1; n<w-1; n++)
        tilemap->setTile(x + n, y, 150, sp::Tilemap::Collision::Solid);
    if (tilemap->getTileIndex(x + w / 2, y - 1) == -1) tilemap->setTile(x + w / 2, y - 1, 166);
    for(int m=0; m<y; m++)
        if (tilemap->getTileIndex(x + w / 2, m) == -1) tilemap->setTile(x + w / 2, m, 182);
    tilemap->setTile(x + w - 1, y, 151, sp::Tilemap::Collision::Solid);
}

void SmbLevelBuilder::bullitTower(int x, int y, int h)
{
    x += page_index * 16;
    
    tilemap->setTile(x, y, 165, sp::Tilemap::Collision::Solid);
    tilemap->setTile(x, y - 1, 181, sp::Tilemap::Collision::Solid);
    for(int n=2; n<h; n++)
        tilemap->setTile(x, y - n, 197, sp::Tilemap::Collision::Solid);
    
    new BullitGenerator(tilemap->getParent(), x, y);
}

void SmbLevelBuilder::bridge(int x, int y, int w)
{
    x += page_index * 16;
    for(int n=0; n<w; n++)
    {
        tilemap->setTile(x + n, y, 112, sp::Tilemap::Collision::Solid);
        tilemap->setTile(x + n, y+1, 96);
    }
}

void SmbLevelBuilder::liftRope(int x)
{
    x += page_index * 16;
    for(int n=0; n<13; n++)
        tilemap->setTile(x, n, 98);
}

void SmbLevelBuilder::trampoline(int x, int y)
{
    x += page_index * 16;
    Trampoline* t = new Trampoline(tilemap->getParent());
    t->setPosition(sp::Vector2d(x + 0.5, y));
}

void SmbLevelBuilder::background()
{
    if (base_type == BaseType::Castle)
    {
        int x = page_index * 16;
        for(int n=0; n<16; n++)
        {
            if (tilemap->getTileIndex(x + n, 1) == -1) tilemap->setTile(x + n, 1, 68);
            if (tilemap->getTileIndex(x + n, 0) == -1) tilemap->setTile(x + n, 0, 84);
        }
        return;
    }
    if (base_type == BaseType::Water)
    {
        int x = page_index * 16;
        for(int n=0; n<16; n++)
        {
            int idx = tilemap->getTileIndex(x + n, global_area_data.water_level);
            if (idx == -1)
            {
                tilemap->setTile(x + n, global_area_data.water_level, 85);
                for(int m=global_area_data.water_level+1; m<16; m++)
                    if (tilemap->getTileIndex(x + n, m) == -1) tilemap->setTile(x + n, m, 69);
            }
            else
            {
                for(int m=global_area_data.water_level+1; m<16; m++)
                    if (tilemap->getTileIndex(x + n, m) == -1) tilemap->setTile(x + n, m, idx, sp::Tilemap::Collision::Solid);
            }
        }
        return;
    }
    switch(scenery)
    {
    case Scenery::None:
        break;
    case Scenery::Mountain:
        switch(page_index % 3)
        {
        case 0:
            hill(0, 2, 2);
            cloud(8, 10, 3);
            bushes(11, 2, 5);
            break;
        case 1:
            hill(0, 2, 1);
            cloud(3, 11, 3);
            bushes(7, 2, 3);
            cloud(11, 10, 5);
            break;
        case 2:
            cloud(4, 11, 4);
            bushes(9, 2, 4);
            break;
        }
        break;
    case Scenery::Clouds:
        switch(page_index % 3)
        {
        case 0:
            cloud(3, 10, 4);
            cloud(9, 6, 3);
            break;
        case 1:
            cloud(2, 11, 4);
            cloud(12, 2, 3);
            break;
        case 2:
            cloud(3, 6, 3);
            cloud(6, 7, 3);
            cloud(14, 2, 3);
            break;
        }
        break;
    case Scenery::Fence:
        switch(page_index % 3)
        {
        case 0:
            cloud(0, 10, 4);
            tree(11, 2, 2);
            tree(13, 2, 3);
            fence(14, 2, 2);
            break;
        case 1:
            fence(0, 2, 2);
            cloud(2, 10, 3);
            tree(5, 2, 3);
            tree(7, 2, 2);
            tree(8, 2, 2);
            cloud(11, 11, 3);
            cloud(14, 10, 5);
            break;
        case 2:
            fence(6, 2, 2);
            tree(8, 2, 2);
            fence(9, 1, 2);
            tree(11, 2, 3);
            cloud(13, 11, 3);
            break;
        }
        break;
    }
}

void SmbLevelBuilder::basicUpTo(int x)
{
    x += page_index * 16;
    while(last_basic_x < x)
        basic(last_basic_x++);
}

void SmbLevelBuilder::basic(int x)
{
    if (surface_size > 0)
    {
        tilemap->setTile(x, 0, floor_tile, sp::Tilemap::Collision::Solid);
        tilemap->setTile(x, 1, floor_tile, sp::Tilemap::Collision::Solid);
        for(int n=1; n<surface_size; n++)
            tilemap->setTile(x, n+1, basic_tile, sp::Tilemap::Collision::Solid);
    }
    for(int n=0; n<ceiling_size; n++)
    {
        tilemap->setTile(x, 12 - n, basic_tile, sp::Tilemap::Collision::Solid);
    }

    for(int n=0; n<middle_size; n++)
    {
        tilemap->setTile(x, 5 + n, basic_tile, sp::Tilemap::Collision::Solid);
    }
}

void SmbLevelBuilder::finalize()
{
}

void SmbLevelBuilder::goomba(int x, int y, int count)
{
    x += page_index * 16;
    for(int n=0; n<count; n++)
        (new Goomba(tilemap->getParent(), x + 1.5 * n, y))->extra_trigger_distance = 1.5 * n;
}

void SmbLevelBuilder::goomba2(int x, int y)
{
    goomba(x, y, 2);
}

void SmbLevelBuilder::goomba3(int x, int y)
{
    goomba(x, y, 3);
}

void SmbLevelBuilder::koopa(int x, int y, Koopa::Type type, Koopa::Behaviour behaviour)
{
    x += page_index * 16;
    new Koopa(tilemap->getParent(), x, y, type, behaviour);
}

void SmbLevelBuilder::koopa2(int x, int y)
{
    x += page_index * 16;
    new Koopa(tilemap->getParent(), x, y);
    (new Koopa(tilemap->getParent(), x + 1.5, y))->extra_trigger_distance = 1.5;
}

void SmbLevelBuilder::koopa3(int x, int y)
{
    x += page_index * 16;
    new Koopa(tilemap->getParent(), x, y);
    (new Koopa(tilemap->getParent(), x + 1.5, y))->extra_trigger_distance = 1.5;
    (new Koopa(tilemap->getParent(), x + 3, y))->extra_trigger_distance = 3.0;
}

void SmbLevelBuilder::blooper(int x, int y)
{
    x += page_index * 16;
    new Blooper(tilemap->getParent(), x, y);
}

void SmbLevelBuilder::podoboo(int x, int y)
{
    x += page_index * 16;
    new Podoboo(tilemap->getParent(), x, y);
}

void SmbLevelBuilder::hammerBrother(int x, int y)
{
    x += page_index * 16;
    new HammerBrother(tilemap->getParent(), x, y);
}

void SmbLevelBuilder::lakitu(int x, int y)
{
    x += page_index * 16;
    new Lakitu(tilemap->getParent(), x, y);
}

void SmbLevelBuilder::buzzyBeetle(int x, int y)
{
    x += page_index * 16;
    new BuzzyBeetle(tilemap->getParent(), x, y);
}

void SmbLevelBuilder::bowser(int x, int y)
{
    stopContinuousGeneration(x);
    x += page_index * 16;
    new Bowser(tilemap->getParent(), x, y);
}

void SmbLevelBuilder::fireBar(int x, int y, FireBar::Type type, FireBar::Size size)
{
    x += page_index * 16;
    FireBar* bar = new FireBar(tilemap->getParent(), type, size);
    bar->setPosition(sp::Vector2d(x + 0.5, y + 0.5));
    bar->setRotation(x * 30 - 90);
}

Lift* SmbLevelBuilder::lift(double x, int y, Lift::Type type, Lift::Size size)
{
    x += page_index * 16;
    Lift* lift = new Lift(tilemap->getParent(), type, size);
    switch(size)
    {
    case Lift::Size::Default:
        lift->setPosition(sp::Vector2d(x + 1.5, y + 0.75));
        break;
    case Lift::Size::Small:
        lift->setPosition(sp::Vector2d(x + 1.0, y + 0.75));
        break;
    case Lift::Size::Tiny:
        lift->setPosition(sp::Vector2d(x + 0.5, y + 0.75));
        break;
    }
    return lift;
}

void SmbLevelBuilder::liftBalance(double x1, int y1, double x2, int y2, Lift::Size size)
{
    Lift* a = lift(x1, y1, Lift::Type::Balance, size);
    Lift* b = lift(x2, y2, Lift::Type::Balance, size);
    a->link(b);
}

void SmbLevelBuilder::startBowserFire(int x)
{
    stopContinuousGeneration(x);
    x += page_index * 16;
    new ContinuousGenerator(tilemap->getParent(), ContinuousGenerator::Type::BowserFire, x);
}

void SmbLevelBuilder::startBullits(int x)
{
    stopContinuousGeneration(x);
    x += page_index * 16;
    new ContinuousGenerator(tilemap->getParent(), ContinuousGenerator::Type::Bullit, x);
}

void SmbLevelBuilder::startCheepCheepJumping(int x)
{
    stopContinuousGeneration(x);
    x += page_index * 16;
    new ContinuousGenerator(tilemap->getParent(), ContinuousGenerator::Type::CheepCheepJump, x);
}

void SmbLevelBuilder::startUnderwaterCheepCheeps(int x)
{
    stopContinuousGeneration(x);
    x += page_index * 16;
    new ContinuousGenerator(tilemap->getParent(), ContinuousGenerator::Type::CheepCheepSwim, x);
}

void SmbLevelBuilder::stopContinuousGeneration(int x)
{
    x += page_index * 16;
    for(auto obj : tilemap->getParent()->getChildren())
    {
        sp::P<ContinuousGenerator> generator = sp::P<sp::Node>(obj);
        if (generator)
            generator->setEndX(x);
    }
}

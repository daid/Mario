#include "randomLevelGenerator.h"
#include "main.h"
#include "questionBlock.h"
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

#include <sp2/scene/scene.h>
#include <sp2/scene/tilemap.h>

void createArea1_1(sp::P<sp::Scene> scene);
void createArea2_1(sp::P<sp::Scene> scene);
void createArea3_1(sp::P<sp::Scene> scene);
void createArea3_2(sp::P<sp::Scene> scene);
void createArea4_1(sp::P<sp::Scene> scene);
void createArea5_1(sp::P<sp::Scene> scene);
void createArea5_2(sp::P<sp::Scene> scene);
void createArea6_1(sp::P<sp::Scene> scene);
void createArea6_2(sp::P<sp::Scene> scene);
void createArea7_1(sp::P<sp::Scene> scene);
void createArea8_1(sp::P<sp::Scene> scene);
void createArea8_2(sp::P<sp::Scene> scene);
void createArea8_3(sp::P<sp::Scene> scene);


RandomLevelGenerator::RandomLevelGenerator()
: chains(3)
{
    sp::P<sp::Scene> scene = new sp::Scene("TMP");
    createArea1_1(scene);
    learn();
    createArea2_1(scene);
    learn();
    createArea3_1(scene);
    learn();
    createArea3_2(scene);
    learn();
    createArea4_1(scene);
    learn();
    createArea5_1(scene);
    learn();
    createArea5_2(scene);
    learn();
    createArea6_1(scene);
    learn();
    createArea6_2(scene);
    learn();
    createArea7_1(scene);
    learn();
    createArea8_1(scene);
    learn();
    createArea8_2(scene);
    learn();
    createArea8_3(scene);
    learn();
    scene.destroy();
}

void RandomLevelGenerator::learn()
{
    sp::P<sp::Scene> scene = sp::Scene::get("TMP");
    
    std::vector<int> data;
    sp::Vector2i size;
    int min_x = 16;
    int max_x = 16;
    for(auto child : scene->getRoot()->getChildren())
    {
        sp::P<sp::Tilemap> tilemap = child;
        sp::P<QuestionBlock> qb = child;
        int index = int(child->getPosition2D().x) + int(child->getPosition2D().y) * size.x;
        if (tilemap)
        {
            size = {16, 16};
            while(true) {
                bool found = false;
                for(int x=0; x<16 && !found; x++)
                    for(int y=0; y<16 && !found; y++)
                        if (tilemap->getTileIndex({size.x + x, y}) != -1)
                            found = true;
                if (!found)
                    break;
                size.x += 1;
            }
            LOG(Debug, size);
            data.resize(size.x * size.y);
            for(int x=0; x<size.x; x++)
                for(int y=0; y<size.y; y++)
                    data[x + y * size.x] = tilemap->getTileCollision({x, y}) == sp::Tilemap::Collision::Open ? -1 : tilemap->getTileIndex({x, y});
        }
        else if (qb)
        {
            switch(qb->getType())
            {
            case QuestionBlock::Type::Normal: data[index] = 0x2000; break;
            case QuestionBlock::Type::Brick:
            case QuestionBlock::Type::BrickCastle:
            case QuestionBlock::Type::BrickUnderground:
                data[index] = 0x2001;
                break;
            case QuestionBlock::Type::Hidden: data[index] = 0x2002; break;
            }
        }
        else if (sp::P<Flagpole>(child))
        {
            max_x = child->getPosition2D().x;
            data[index] = 0x1000;
        }
        else if (sp::P<Goomba>(child))
            data[index] = 0x1001;
        else if (sp::P<Koopa>(child))
            data[index] = 0x1002;
        else if (sp::P<HammerBrother>(child))
            data[index] = 0x1003;
        else if (sp::P<BuzzyBeetle>(child))
            data[index] = 0x1004;
        else if (sp::P<Lakitu>(child))
            data[index] = 0x1005;
        else if (sp::P<Trampoline>(child))
            data[index] = 0x3001;
        else if (sp::P<Coin>(child))
            data[index] = 0x3002;
        else if (sp::P<PiranhaPlant>(child))
        {} //Will be placed at 0x80 tiles
        else if (sp::P<BullitGenerator>(child))
        {} //Will be placed at 0xa5 tiles
        else
            LOG(Debug, child);
    }
    
    start = buildDataLine(data, size, min_x - 1);
    chains.seed(start);
    for(int x=min_x;x<max_x;x++)
        chains.addLearning(buildDataLine(data, size, x));

    for(auto child : scene->getRoot()->getChildren())
        child.destroy();
}

std::u32string RandomLevelGenerator::buildDataLine(const std::vector<int>& data, sp::Vector2i size, int x)
{
    std::u32string result;
    for(int y=size.y-1;y>=0; y--)
        result.push_back(data[x + y * size.x]);
    return result;
}

void RandomLevelGenerator::generate(sp::P<sp::Scene> scene, int seed)
{
    std::mt19937_64 random_engine;
    random_engine.seed(seed);

    global_area_data.start_position = sp::Vector2d(2, 2);
    sp::P<sp::Tilemap> tilemap = new sp::Tilemap(scene->getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    window->setClearColor(sp::Color(107/255.0f, 136/255.0f, 255/255.0f));
    global_area_data.view_limit = std::numeric_limits<double>::max();
    global_area_data.water_level = -10;
    global_area_data.music_name = "Overworld";

    chains.seed(start);
    for(int x=0; x<16; x++)
    {
        tilemap->setTile({x, 0}, 0, sp::Tilemap::Collision::Solid);
        tilemap->setTile({x, 1}, 0, sp::Tilemap::Collision::Solid);
    }
    int width = 16*16;
    for(int x=16;x<width;x++)
    {
        std::u32string current = chains.getNext(random_engine);
        for(unsigned int y=0; y<current.length(); y++)
        {
            unsigned int nr = current[current.length() - y - 1];
            if (nr < 256)
                tilemap->setTile({x, y}, nr, sp::Tilemap::Collision::Solid);
            
            switch(nr)
            {
            case 0x80: new PiranhaPlant(scene->getRoot(), x + 0.5, y); break;
            case 0xa5: new BullitGenerator(scene->getRoot(), x, y); break;
            case 0x1001: new Goomba(scene->getRoot(), x, y); break;
            case 0x1002: new Koopa(scene->getRoot(), x, y); break;
            case 0x1003: new HammerBrother(scene->getRoot(), x, y); break;
            case 0x1004: new BuzzyBeetle(scene->getRoot(), x, y); break;
            case 0x1005: new Lakitu(scene->getRoot(), x, y); break;
            case 0x2000: (new QuestionBlock(tilemap, QuestionBlock::Type::Normal, QuestionBlock::Contents::Coin))->setPosition(sp::Vector2d(x + 0.5, y + 0.5)); break;
            case 0x2001: (new QuestionBlock(tilemap, QuestionBlock::Type::Brick, QuestionBlock::Contents::Coin))->setPosition(sp::Vector2d(x + 0.5, y + 0.5)); break;
            case 0x2002: (new QuestionBlock(tilemap, QuestionBlock::Type::Hidden, QuestionBlock::Contents::Coin))->setPosition(sp::Vector2d(x + 0.5, y + 0.5)); break;
            case 0x3001: (new Trampoline(scene->getRoot()))->setPosition(sp::Vector2d(x + 0.5, y)); break;
            case 0x3002: (new Coin(scene->getRoot()))->setPosition(sp::Vector2d(x + 0.5, y + 0.5)); break;
            case 0xffffffff: break;
            default:
                if (nr > 255)
                    LOG(Debug, sp::string::hex(nr));
                break;
            }
        }
    }
    width += 1;
    for(int x=0; x<16; x++)
    {
        tilemap->setTile({width+x, 0}, 0, sp::Tilemap::Collision::Solid);
        tilemap->setTile({width+x, 1}, 0, sp::Tilemap::Collision::Solid);
    }
    tilemap->setTile({width, 2}, 1, sp::Tilemap::Collision::Solid);
    for(int n=1; n<8; n++)
        tilemap->setTile({width, 2 + n}, 30);
    tilemap->setTile({width, 2 + 8}, 14);
    
    new Flagpole(tilemap->getParent(), width + 0.5);
}

#include "editor.h"
#include "savegame.h"
#include "main.h"

#include <sp2/scene/camera.h>
#include <sp2/graphics/meshdata.h>
#include <sp2/graphics/textureManager.h>


class EditorCursor : public sp::Node
{
public:
    EditorCursor(sp::P<sp::Node> parent, InputController& controller, EditorScene& editor)
    : sp::Node(parent), controller(controller), editor(editor)
    {
        render_data.type = sp::RenderData::Type::Normal;
        setGfx("tiles.png", 1); 
        render_data.shader = sp::Shader::get("internal:basic.shader");
        render_data.color.a = 0.5;
        
        position = sp::Vector2i(5, 1);
        setPosition(sp::Vector2d(position) + sp::Vector2d(0.5, 0.5));
        active = false;
    }
    
    void onFixedUpdate() override
    {
        if (controller.left.getDown() && position.x > 0) position.x--;
        if (controller.right.getDown() && position.x < editor.level_data->width - 1) position.x++;
        if (controller.down.getDown() && position.y > 0) position.y--;
        if (controller.up.getDown() && position.y < editor.level_data->height - 1) position.y++;
        if (controller.left.get() || controller.right.get() || controller.down.get() || controller.up.get())
        {
            active = true;
            if (repeat_delay > 0)
            {
                repeat_delay--;
            }
            else
            {
                if (controller.left.get() && position.x > 0) position.x--;
                if (controller.right.get() && position.x < editor.level_data->width - 1) position.x++;
                if (controller.down.get() && position.y > 0) position.y--;
                if (controller.up.get() && position.y < editor.level_data->height - 1) position.y++;
                repeat_delay = 5;
            }
        }
        else
        {
            repeat_delay = 30;
        }
        
        if (controller.running.get()) editor.setTile(position.x, position.y, LevelData::Tile::Type::Open);
        if (controller.jump.get()) editor.setTile(position.x, position.y, tile_type);
        if (controller.extra1.getDown())
        {
            tile_type = LevelData::Tile::Type(int(tile_type) + 1);
            if (tile_type == LevelData::Tile::Type::Count)
                tile_type = LevelData::Tile::Type::Brick;
            updateTileGfx();
        }
        if (controller.extra2.getDown())
        {
            tile_type = LevelData::Tile::Type(int(tile_type) - 1);
            if (tile_type == LevelData::Tile::Type::Open)
                tile_type = LevelData::Tile::Type(int(LevelData::Tile::Type::Count) - 1);
            updateTileGfx();
        }
        if (controller.extra0.getDown())
            editor.adjustTile(position.x, position.y);

        if (controller.start.getDown())
        {
            loadStage(editor.level_data);
            return;
        }
        
        if (active)
        {
            setPosition(sp::Vector2d(position) + sp::Vector2d(0.5, 0.5));
            
            sp::P<sp::Camera> camera = getScene()->getCamera();
            sp::Vector2d camera_position = camera->getPosition2D();
            if (camera_position.x < position.x - 6)
                camera_position.x += 0.1;
            if (camera_position.x > position.x + 6)
                camera_position.x -= 0.1;
            camera_position.x = std::min(camera_position.x, editor.level_data->width - 8.0);
            camera_position.x = std::max(camera_position.x, 8.0);
            camera->setPosition(camera_position);
        }
    }
    
    void updateTileGfx()
    {
        switch(tile_type)
        {
        case LevelData::Tile::Type::Open: break;
        case LevelData::Tile::Type::Brick: setGfx("tiles.png", 1); break;
        case LevelData::Tile::Type::Ground: setGfx("tiles.png", 0); break;
        case LevelData::Tile::Type::Block: setGfx("tiles.png", 16); break;
        case LevelData::Tile::Type::Coin: setGfx("editor_overlay_tiles.png", 17); break;
        case LevelData::Tile::Type::QuestionBlock: setGfx("editor_overlay_tiles.png", 1); break;
        
        case LevelData::Tile::Type::Pipe: setGfx("tiles.png", 136); break;
        case LevelData::Tile::Type::PipeRed: setGfx("tiles.png", 184); break;
        case LevelData::Tile::Type::Trampoline: setGfx("editor_overlay_tiles.png", 18); break;
        case LevelData::Tile::Type::Island: setGfx("tiles.png", 137); break;
        case LevelData::Tile::Type::MushroomIsland: setGfx("tiles.png", 137 + 16); break;

        case LevelData::Tile::Type::BullitTower: setGfx("tiles.png", 165); break;
        case LevelData::Tile::Type::FirebarLeft: setGfx("editor_overlay_tiles.png", 43); break;
        case LevelData::Tile::Type::FirebarRight: setGfx("editor_overlay_tiles.png", 44); break;
        
        case LevelData::Tile::Type::Goomba: setGfx("editor_overlay_tiles.png", 8); break;
        case LevelData::Tile::Type::KoopaGreen: setGfx("editor_overlay_tiles.png", 9); break;
        case LevelData::Tile::Type::KoopaRed: setGfx("editor_overlay_tiles.png", 25); break;
        case LevelData::Tile::Type::KoopaParatrooperGreen: setGfx("editor_overlay_tiles.png", 11); break;
        case LevelData::Tile::Type::KoopaParatrooperRed: setGfx("editor_overlay_tiles.png", 27); break;
        case LevelData::Tile::Type::Blooper: setGfx("editor_overlay_tiles.png", 40); break;
        case LevelData::Tile::Type::Podoboo: setGfx("editor_overlay_tiles.png", 10); break;
        case LevelData::Tile::Type::HammerBrother: setGfx("editor_overlay_tiles.png", 41); break;
        case LevelData::Tile::Type::Lakitu: setGfx("editor_overlay_tiles.png", 42); break;
        case LevelData::Tile::Type::BuzzyBeetle: setGfx("editor_overlay_tiles.png", 24); break;
        case LevelData::Tile::Type::Bowser: setGfx("editor_overlay_tiles.png", 26); break;

        case LevelData::Tile::Type::Flagpole: setGfx("editor_overlay_tiles.png", 32); break;
        case LevelData::Tile::Type::Princess: setGfx("editor_overlay_tiles.png", 2); break;

        case LevelData::Tile::Type::Count: break;
        }
    }
    
    void setGfx(sp::string texture, int tile_index)
    {
        float x = tile_index % 16;
        float y = tile_index / 16;
        render_data.mesh = sp::MeshData::createQuad(sp::Vector2f(0.9, 0.9), sp::Vector2f(x / 16, y / 16), sp::Vector2f((x + 1) / 16, (y + 1) / 16));
        render_data.texture = sp::textureManager.get(texture);
    }
    
    sp::Vector2i position;
    InputController& controller;
    EditorScene& editor;
    int repeat_delay;
    bool active;
    
    LevelData::Tile::Type tile_type = LevelData::Tile::Type::Brick;
};


LevelData::LevelData()
{
    for(int x=0; x<width; x++)
    {
        tiles[x][0].type = Tile::Type::Ground;
        tiles[x][1].type = Tile::Type::Ground;
    }
}

int LevelData::getTileIndex(int x, int y)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
        return -1;
    switch(tiles[x][y].type)
    {
    case LevelData::Tile::Type::Open:
        for(int n=y+1; n<height; n++)
        {
            if (tiles[x][n].type == LevelData::Tile::Type::Island)
            {
                if (x > 0 && x < width - 1 && tiles[x - 1][n].type == LevelData::Tile::Type::Island && tiles[x + 1][n].type == LevelData::Tile::Type::Island)
                    return 18;
            }
        }
        break;
    case LevelData::Tile::Type::Brick: return 1;
    case LevelData::Tile::Type::Ground: return 0;
    case LevelData::Tile::Type::Block: return 16;
    case LevelData::Tile::Type::Coin: break;
    case LevelData::Tile::Type::QuestionBlock: break;
            
    case LevelData::Tile::Type::Pipe:
    case LevelData::Tile::Type::PipeRed:
        {
            int tile = 128;
            int n = 0;
            while(x - n > 0 && tiles[x-1-n][y].type == tiles[x][y].type)
                n++;
            if (n % 2 == 1)
                tile += 1;
            else if (x >= width - 1 || tiles[x+1][y].type != tiles[x][y].type)
                tile += 8;
            if (isTileSolid(x, y + 1))
            {
                tile+=16;
                if (!isTileSolid(x, y - 1))
                    tile += 16;
            }
            if (tiles[x][y].type == LevelData::Tile::Type::PipeRed)
                tile += 48;
            return tile;
        }
    case LevelData::Tile::Type::Island:
        if (isTileSolid(x - 1, y) && isTileSolid(x + 1, y))
            return 134;
        if (isTileSolid(x - 1, y))
            return 135;
        if (isTileSolid(x + 1, y))
            return 133;
        return 137;
    case LevelData::Tile::Type::MushroomIsland:
        if (isTileSolid(x - 1, y) && isTileSolid(x + 1, y))
            return 134 + 16;
        if (isTileSolid(x - 1, y))
            return 135 + 16;
        if (isTileSolid(x + 1, y))
            return 133 + 16;
        return 137 + 16;

    case LevelData::Tile::Type::Trampoline: break;
    case LevelData::Tile::Type::BullitTower:
        if (y < height - 1 && tiles[x][y+1].type == LevelData::Tile::Type::BullitTower)
        {
            if (y < height - 2 && tiles[x][y+2].type == LevelData::Tile::Type::BullitTower)
                return 197;
            return 181;
        }
        return 165;
    case LevelData::Tile::Type::FirebarLeft:
    case LevelData::Tile::Type::FirebarRight:
        return 3;
    
    case LevelData::Tile::Type::Goomba: break;
    case LevelData::Tile::Type::KoopaGreen: break;
    case LevelData::Tile::Type::KoopaRed: break;
    case LevelData::Tile::Type::KoopaParatrooperGreen: break;
    case LevelData::Tile::Type::KoopaParatrooperRed: break;
    case LevelData::Tile::Type::Blooper: break;
    case LevelData::Tile::Type::Podoboo: break;
    case LevelData::Tile::Type::HammerBrother: break;
    case LevelData::Tile::Type::Lakitu: break;
    case LevelData::Tile::Type::BuzzyBeetle: break;
    case LevelData::Tile::Type::Bowser: break;
    case LevelData::Tile::Type::Flagpole: break;
    case LevelData::Tile::Type::Princess: break;
    case LevelData::Tile::Type::Count: break;
    }
    return -1;
}

bool LevelData::isTileSolid(int x, int y)
{
    if (x < 0 || y < 0 || x >= width || y >= height)
        return false;
    switch(tiles[x][y].type)
    {
    case LevelData::Tile::Type::Open: return false;
    case LevelData::Tile::Type::Brick: return true;
    case LevelData::Tile::Type::Ground: return true;
    case LevelData::Tile::Type::Block: return true;
    case LevelData::Tile::Type::Coin: return false;
    case LevelData::Tile::Type::QuestionBlock: return true;
            
    case LevelData::Tile::Type::Pipe: return true;
    case LevelData::Tile::Type::PipeRed: return true;
    case LevelData::Tile::Type::Island: return true;
    case LevelData::Tile::Type::MushroomIsland: return true;
    case LevelData::Tile::Type::Trampoline: return false;
    case LevelData::Tile::Type::BullitTower: return true;
    case LevelData::Tile::Type::FirebarLeft: return true;
    case LevelData::Tile::Type::FirebarRight: return true;
    
    case LevelData::Tile::Type::Goomba: return false;
    case LevelData::Tile::Type::KoopaGreen: return false;
    case LevelData::Tile::Type::KoopaRed: return false;
    case LevelData::Tile::Type::KoopaParatrooperGreen: break;
    case LevelData::Tile::Type::KoopaParatrooperRed: break;
    case LevelData::Tile::Type::Blooper: return false;
    case LevelData::Tile::Type::Podoboo: return false;
    case LevelData::Tile::Type::HammerBrother: return false;
    case LevelData::Tile::Type::Lakitu: return false;
    case LevelData::Tile::Type::BuzzyBeetle: return false;
    case LevelData::Tile::Type::Bowser: return false;
    case LevelData::Tile::Type::Flagpole: return false;
    case LevelData::Tile::Type::Princess: return false;

    case LevelData::Tile::Type::Count: return false;
    }
    return false;
}

EditorScene::EditorScene()
: sp::Scene("editor")
{
    disable();

    level_data = new LevelData();
}

void EditorScene::onEnable()
{
    main_tilemap = new sp::Tilemap(getRoot(), "tiles.png", 1.0, 1.0, 16, 16);
    overlay_tilemap = new sp::Tilemap(getRoot(), "editor_overlay_tiles.png", 1.0, 1.0, 16, 16);

    for(int x=0; x<level_data->width; x++)
    {
        for(int y=0; y<level_data->height; y++)
        {
            updateTilemap(x, y);
        }
    }
    
    camera = new sp::Camera(getRoot());
    camera->setOrtographic(8.0, sp::Camera::Direction::Horizontal);
    camera->setPosition(sp::Vector2d(8, 6.5));
    setDefaultCamera(camera);
    
    for(int n=0; n<save_game.getPlayerCount(); n++)
        new EditorCursor(getRoot(), controller[n], *this);
}

void EditorScene::onDisable()
{
    for(auto child : getRoot()->getChildren())
        delete child;
}

void EditorScene::setTile(int x, int y, LevelData::Tile::Type type)
{
    level_data->tiles[x][y].type = type;
    level_data->tiles[x][y].contents = LevelData::Tile::Contents::None;
    if (type == LevelData::Tile::Type::QuestionBlock)
        level_data->tiles[x][y].contents = LevelData::Tile::Contents::Coin;
    
    
    for(int n=std::max(0, x-1);n<x+2 && n<level_data->width; n++)
    {
        for(int m=0;m<level_data->height; m++)
            updateTilemap(n, m);
    }
}

void EditorScene::adjustTile(int x, int y)
{
    switch(level_data->tiles[x][y].type)
    {
    case LevelData::Tile::Type::Open:
    case LevelData::Tile::Type::Brick:
    case LevelData::Tile::Type::QuestionBlock:
        level_data->tiles[x][y].contents = LevelData::Tile::Contents(int(level_data->tiles[x][y].contents) + 1);
        if (level_data->tiles[x][y].contents == LevelData::Tile::Contents::Count)
            level_data->tiles[x][y].contents = LevelData::Tile::Contents::Coin;
        break;
    default:
        break;
    }
    updateTilemap(x, y);
}

void EditorScene::updateTilemap(int x, int y)
{
    main_tilemap->setTile(x, y, level_data->getTileIndex(x, y));
    overlay_tilemap->setTile(x, y, -1);
    switch(level_data->tiles[x][y].type)
    {
    case LevelData::Tile::Type::Open:
        if (level_data->tiles[x][y].contents != LevelData::Tile::Contents::None)
            main_tilemap->setTile(x, y, 5);
        break;
    case LevelData::Tile::Type::Brick: break;
    case LevelData::Tile::Type::Ground: break;
    case LevelData::Tile::Type::Block: break;
    case LevelData::Tile::Type::Coin: overlay_tilemap->setTile(x, y, 17); break;
    case LevelData::Tile::Type::QuestionBlock: main_tilemap->setTile(x, y, 3); break;
            
    case LevelData::Tile::Type::Pipe: break;
    case LevelData::Tile::Type::PipeRed: break;
    case LevelData::Tile::Type::Island: break;
    case LevelData::Tile::Type::MushroomIsland: break;
    case LevelData::Tile::Type::Trampoline: overlay_tilemap->setTile(x, y, 18); break;
    case LevelData::Tile::Type::BullitTower: break;
    case LevelData::Tile::Type::FirebarLeft: overlay_tilemap->setTile(x, y, 43); break;
    case LevelData::Tile::Type::FirebarRight: overlay_tilemap->setTile(x, y, 44); break;
    
    case LevelData::Tile::Type::Goomba: overlay_tilemap->setTile(x, y, 8); break;
    case LevelData::Tile::Type::KoopaGreen: overlay_tilemap->setTile(x, y, 9); break;
    case LevelData::Tile::Type::KoopaRed: overlay_tilemap->setTile(x, y, 25); break;
    case LevelData::Tile::Type::KoopaParatrooperGreen: overlay_tilemap->setTile(x, y, 11); break;
    case LevelData::Tile::Type::KoopaParatrooperRed: overlay_tilemap->setTile(x, y, 27); break;
    case LevelData::Tile::Type::Blooper: overlay_tilemap->setTile(x, y, 40); break;
    case LevelData::Tile::Type::Podoboo: overlay_tilemap->setTile(x, y, 10); break;
    case LevelData::Tile::Type::HammerBrother: overlay_tilemap->setTile(x, y, 41); break;
    case LevelData::Tile::Type::Lakitu: overlay_tilemap->setTile(x, y, 42); break;
    case LevelData::Tile::Type::BuzzyBeetle: overlay_tilemap->setTile(x, y, 24); break;
    case LevelData::Tile::Type::Bowser: overlay_tilemap->setTile(x, y, 26); break;
    case LevelData::Tile::Type::Flagpole: overlay_tilemap->setTile(x, y, 32); break;
    case LevelData::Tile::Type::Princess: overlay_tilemap->setTile(x, y, 2); break;
    case LevelData::Tile::Type::Count: break;
    }
    switch(level_data->tiles[x][y].contents)
    {
    case LevelData::Tile::Contents::None: break;
    case LevelData::Tile::Contents::Coin: overlay_tilemap->setTile(x, y, 17); break;
    case LevelData::Tile::Contents::MultiCoin: overlay_tilemap->setTile(x, y, 33); break;
    case LevelData::Tile::Contents::Upgrade: overlay_tilemap->setTile(x, y, 0); break;
    case LevelData::Tile::Contents::Star: overlay_tilemap->setTile(x, y, 48); break;
    case LevelData::Tile::Contents::Life: overlay_tilemap->setTile(x, y, 16); break;
    case LevelData::Tile::Contents::Vine: overlay_tilemap->setTile(x, y, 34); break;
    case LevelData::Tile::Contents::Count: break;
    }
}

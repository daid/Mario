#ifndef EDITOR_H
#define EDITOR_H

#include <sp2/scene/scene.h>
#include <sp2/scene/tilemap.h>
#include "serializer.h"

class LevelData : public ISerializable
{
public:
    class Tile : public ISerializable
    {
    public:
        enum class Type
        {
            Open,
            Brick,
            Ground,
            Block,
            Coin,
            QuestionBlock,
            
            Pipe,
            PipeRed,
            Island,
            MushroomIsland,
            
            Trampoline,
            BullitTower,
            FirebarLeft,
            FirebarRight,
            
            Goomba,
            KoopaGreen,
            KoopaRed,
            KoopaParatrooperGreen,
            KoopaParatrooperRed,
            Blooper,
            Podoboo,
            HammerBrother,
            Lakitu,
            BuzzyBeetle,
            Bowser,
            
            Flagpole,
            Princess,
            
            Count
        };
        enum class Contents
        {
            None,
            Coin,
            MultiCoin,
            Upgrade,
            Star,
            Life,
            Vine,
            
            Count
        };
        
        Type type = Type::Open;
        Contents contents = Contents::None;
        
        virtual void serialize(Serializer::Handler& handler) override;
    };
    
    LevelData();
    
    int getTileIndex(int x, int y);
    bool isTileSolid(int x, int y);
    
    virtual void serialize(Serializer::Handler& handler) override;
    
    static constexpr int width = 10 * 16;
    static constexpr int height = 13;
    Tile tiles[width][height];
};

class EditorScene : public sp::Scene
{
public:
    EditorScene();

    virtual void onEnable() override;
    virtual void onDisable() override;
    
    LevelData* level_data = nullptr;
    
    void save(int index);
    void load(int index);
    
    void setTile(int x, int y, LevelData::Tile::Type type);
    void adjustTile(int x, int y);
private:
    void updateTilemap(int x, int y);
    
    sp::P<sp::Tilemap> main_tilemap;
    sp::P<sp::Tilemap> overlay_tilemap;
    sp::P<sp::Camera> camera;
};

#endif//EDITOR_H

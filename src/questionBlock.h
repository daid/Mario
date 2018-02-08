#ifndef QUESTION_BLOCK_H
#define QUESTION_BLOCK_H

#include <sp2/scene/node.h>
#include <sp2/scene/tilemap.h>

class QuestionBlock : public sp::Node
{
public:
    enum class Type
    {
        Normal,
        Brick,
        BrickUnderground,
        BrickCastle,
        Hidden
    };
    enum class Contents
    {
        Coin,
        MultiCoin,
        Upgrade,
        Star,
        Vine,
        Life
    };

    QuestionBlock(sp::P<sp::Tilemap> tilemap, Type type=Type::Normal, Contents contents=Contents::Coin);

    virtual void onCollision(sp::CollisionInfo& info) override;
    virtual void onFixedUpdate() override;
private:
    sp::P<sp::Tilemap> tilemap;
    
    Contents contents;
    Type type;
    enum class State {
        Idle,
        Bump,
        Destroy
    } state = State::Idle;
    sp::Vector2d start_position;
    int multi_coin_count = 10;
};

#endif//QUESTION_BLOCK_H

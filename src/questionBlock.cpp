#include "questionBlock.h"

#include "playerPawn.h"
#include "savegame.h"
#include "vine.h"
#include "pickup/smb/upgrade.h"
#include "pickup/smb/life.h"
#include "pickup/smb/star.h"

#include <sp2/collision/2d/box.h>
#include <sp2/audio/sound.h>
#include <sp2/graphics/spriteAnimation.h>


class CoinEffect : public sp::Node
{
public:
    CoinEffect(sp::P<sp::Node> parent)
    : sp::Node(parent)
    {
        setAnimation(sp::SpriteAnimation::load("coinEffect.txt"));
        animationPlay("Default");
        render_data.order = 2;
        
        velocity = 20.0;
    }

    void onUpdate(float delta)
    {
        velocity -= delta * 60.0;
        setPosition(getPosition2D() + sp::Vector2d(0, velocity * delta));
        if (velocity < -15.0)
            delete this;
    }

private:
    double velocity;
};


QuestionBlock::QuestionBlock(sp::P<sp::Tilemap> tilemap, Type type, Contents contents)
: sp::Node(tilemap->getParent()), tilemap(tilemap), contents(contents), type(type)
{
    sp::collision::Box2D shape(1, 1);
    shape.type = sp::collision::Shape::Type::Static;
    shape.fixed_rotation = true;
    
    setAnimation(sp::SpriteAnimation::load("question_block.txt"));
    switch(type)
    {
    case Type::Normal:
        animationPlay("Default");
        break;
    case Type::Brick:
        animationPlay("Brick");
        break;
    case Type::BrickUnderground:
        animationPlay("BrickUnderground");
        break;
    case Type::BrickCastle:
        animationPlay("BrickCastle");
        break;
    case Type::Hidden:
        shape.type = sp::collision::Shape::Type::Sensor;
        break;
    }
    setCollisionShape(shape);
    render_data.order = -1;
}

void QuestionBlock::onCollision(sp::CollisionInfo& info)
{
    if (state != State::Idle)
        return;

    sp::P<PlayerPawn> player = info.other;
    if (player)
    {
        sp::Vector2d velocity_difference = getLinearVelocity2D() - player->getLinearVelocity2D();
        if ((info.normal.y < -0.9 && isSolid()) || (!isSolid() && velocity_difference.y < -0.1))
        {
            start_position = getPosition2D();
            state = State::Bump;
            setPosition(start_position + sp::Vector2d(0, 4.0/16.0));
            switch(contents)
            {
            case Contents::Coin:
                (new CoinEffect(getParent()))->setPosition(getPosition2D() + sp::Vector2d(0, 1));
                sp::audio::Sound::play("sfx/smb_coin.wav");
                save_game.addCoin();
                break;
            case Contents::MultiCoin:
                (new CoinEffect(getParent()))->setPosition(getPosition2D() + sp::Vector2d(0, 1));
                sp::audio::Sound::play("sfx/smb_coin.wav");
                save_game.addCoin();
                break;
            case Contents::Upgrade:
                if (player->getUpgradeLevel() == 0)
                    (new UpgradePickup(getParent(), UpgradePickup::Type::Mushroom))->setPosition(getPosition2D());
                else
                    (new UpgradePickup(getParent(), UpgradePickup::Type::Flower))->setPosition(getPosition2D());
                sp::audio::Sound::play("sfx/smb_powerup_appears.wav");
                break;
            case Contents::Star:
                (new StarPickup(getParent()))->setPosition(getPosition2D());
                sp::audio::Sound::play("sfx/smb_powerup_appears.wav");
                break;
            case Contents::Vine:
                (new Vine(getParent()))->setPosition(sp::Vector2d(int(getPosition2D().x) + 0.5, int(getPosition2D().y) + 1.0));
                break;
            case Contents::Life:
                (new LifePickup(getParent()))->setPosition(getPosition2D());
                sp::audio::Sound::play("sfx/smb_powerup_appears.wav");
                break;
            }
            if (contents == Contents::MultiCoin && multi_coin_count > 0)
                multi_coin_count--;
            else
                animationPlay("Empty");

            if (type == Type::Hidden)
            {
                removeCollisionShape();
                sp::collision::Box2D shape(1, 1);
                shape.type = sp::collision::Shape::Type::Static;
                shape.fixed_rotation = true;
                setCollisionShape(shape);
                type = Type::Normal;
            }
        }
    }
}

void QuestionBlock::onFixedUpdate()
{
    if (state == State::Bump)
    {
        sp::Vector2d position = getPosition2D();
        position.y -= 1.0/32.0;
        if (position.y <= start_position.y)
        {
            position = start_position;
            if (contents != Contents::MultiCoin || multi_coin_count < 1)
            {
                tilemap->setTile(getPosition2D().x, getPosition2D().y, 3, sp::Tilemap::Collision::Solid);
                state = State::Destroy;
                return;
            }
            state = State::Idle;
        }
        setPosition(position);
    }
    if (state == State::Destroy)
    {
        delete this;
    }
}

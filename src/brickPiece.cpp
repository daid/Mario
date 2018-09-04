#include "brickPiece.h"

#include <sp2/graphics/spriteAnimation.h>


BrickPiece::BrickPiece(sp::P<sp::Node> parent, double x, double y, bool left, bool top)
: sp::Node(parent)
{
    setAnimation(sp::SpriteAnimation::load("brick_piece.txt"));
    animationPlay("Brick");

    render_data.order = 2;
    
    setPosition(sp::Vector2d(x, y));
    if (top)
        velocity = sp::Vector2d(-6, 15);
    else
        velocity = sp::Vector2d(-5, 10);
    if (!left)
    {
        animationSetFlags(sp::SpriteAnimation::FlipFlag);
        velocity.x = -velocity.x;
    }
}

void BrickPiece::onUpdate(float delta)
{
    setPosition(getPosition2D() + velocity * double(delta));
    velocity.y -= delta * 100;
    
    if (getPosition2D().y < -1)
        delete this;
}

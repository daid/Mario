#ifndef BRICK_PIECE_H
#define BRICK_PIECE_H

#include <sp2/scene/node.h>

class BrickPiece : public sp::Node
{
public:
    BrickPiece(sp::P<sp::Node> parent, double x, double y, bool left, bool top);

    virtual void onUpdate(float delta) override;
private:
    sp::Vector2d velocity;
};

#endif//BRICK_PIECE_H

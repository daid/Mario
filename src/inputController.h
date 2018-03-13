#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <sp2/io/keybinding.h>

class InputController
{
public:
    InputController(int index)
    : left(sp::string(index) + "_left", "Left")
    , right(sp::string(index) + "_right", "Right")
    , up(sp::string(index) + "_up", "Up")
    , down(sp::string(index) + "_down", "Down")
    , running(sp::string(index) + "_running", "Z")
    , jump(sp::string(index) + "_jump", "Space")
    {
        if (index == 1)
        {
            left.setKey("A");
            right.setKey("D");
            up.setKey("W");
            down.setKey("S");
            running.setKey("E");
            jump.setKey("Q");
        }
    }
    
    sp::io::Keybinding left;
    sp::io::Keybinding right;
    sp::io::Keybinding up;
    sp::io::Keybinding down;
    sp::io::Keybinding running;
    sp::io::Keybinding jump;
};

#endif//INPUT_CONTROLLER_H

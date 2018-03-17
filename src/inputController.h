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
    , extra0(sp::string(index) + "_extra0", "X")
    , extra1(sp::string(index) + "_extra1", "C")
    , extra2(sp::string(index) + "_extra2", "V")
    , extra3(sp::string(index) + "_extra3", "B")
    , start(sp::string(index) + "_start", "Num1")
    {
        if (index == 1)
        {
            left.setKey("A");
            right.setKey("D");
            up.setKey("W");
            down.setKey("S");
            running.setKey("E");
            jump.setKey("Q");
            extra0.setKey("R");
            extra1.setKey("F");
            extra2.setKey("T");
            extra3.setKey("G");
            start.setKey("Num2");
        }
    }
    
    sp::io::Keybinding left;
    sp::io::Keybinding right;
    sp::io::Keybinding up;
    sp::io::Keybinding down;
    sp::io::Keybinding running;
    sp::io::Keybinding jump;
    sp::io::Keybinding extra0;
    sp::io::Keybinding extra1;
    sp::io::Keybinding extra2;
    sp::io::Keybinding extra3;
    sp::io::Keybinding start;
};

#endif//INPUT_CONTROLLER_H

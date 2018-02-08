#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <sp2/io/keybinding.h>

class InputController
{
public:
    InputController(int index)
    : left(sp::string(index) + "_left", sf::Keyboard::A)
    , right(sp::string(index) + "_right", sf::Keyboard::D)
    , up(sp::string(index) + "_up", sf::Keyboard::W)
    , down(sp::string(index) + "_down", sf::Keyboard::S)
    , running(sp::string(index) + "_running", sf::Keyboard::LShift)
    , jump(sp::string(index) + "_jump", sf::Keyboard::Space)
    {
        if (index == 1)
        {
            left.setKey(sf::Keyboard::Left);
            right.setKey(sf::Keyboard::Right);
            up.setKey(sf::Keyboard::Up);
            down.setKey(sf::Keyboard::Down);
            running.setKey(sf::Keyboard::RShift);
            jump.setKey(sf::Keyboard::Return);
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

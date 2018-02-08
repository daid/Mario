#ifndef INPUT_CONTROLLER_H
#define INPUT_CONTROLLER_H

#include <sp2/io/keybinding.h>

class InputController
{
public:
    InputController(int index)
    : left(sp::string(index) + "_left", sf::Keyboard::Left)
    , right(sp::string(index) + "_right", sf::Keyboard::Right)
    , up(sp::string(index) + "_up", sf::Keyboard::Up)
    , down(sp::string(index) + "_down", sf::Keyboard::Down)
    , running(sp::string(index) + "_running", sf::Keyboard::Z)
    , jump(sp::string(index) + "_jump", sf::Keyboard::Space)
    {
        if (index == 1)
        {
            left.setKey(sf::Keyboard::A);
            right.setKey(sf::Keyboard::D);
            up.setKey(sf::Keyboard::W);
            down.setKey(sf::Keyboard::S);
            running.setKey(sf::Keyboard::Q);
            jump.setKey(sf::Keyboard::E);
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

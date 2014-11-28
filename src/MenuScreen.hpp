#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "utilities/InputHandler.hpp"
#include "utilities/Button.hpp"

class MenuScreen{
    std::vector<sf::Sprite> buttonVector;
    public:
        MenuScreen(){};
        void update(InputHandler& input);
        void draw(sf::RenderWindow& window);
};
#endif

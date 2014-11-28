#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "utilities/InputHandler.hpp"
#include "utilities/Assets.hpp"
#include "utilities/Button.hpp"

class MenuScreen{
    private:
        sf::RenderWindow* window;
        InputHandler* input;
        std::vector<std::pair<std::string, sf::Sprite*>> buttonVector;
        bool gameStart = false;
        bool buttonClicked(const sf::Sprite&);
    public:
        MenuScreen(sf::RenderWindow& screen, InputHandler& handler);
        void update();
        void draw();
        bool getGameStart();
};
#endif

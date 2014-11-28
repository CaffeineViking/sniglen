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
        InputHandler* input;
        sf::RenderWindow* window;
        std::vector<std::pair<std::string, sf::Sprite*>> buttonVector;
        bool gameStart = false;
        bool buttonClicked(const sf::Sprite&);
    public:
        MenuScreen(sf::RenderWindow& screen, InputHandler& handler): window{&screen}, input{&handler} {
            buttonVector.push_back(std::make_pair("Start", new sf::Sprite(Assets::LOAD_TEXTURE("test2.jpg"))));
            buttonVector.back().second->setOrigin(buttonVector.back().second->getTexture()->getSize().x/2, buttonVector.back().second->getTexture()->getSize().y/2);
            buttonVector.back().second->setPosition({window->getSize().x/2, window->getSize().y/2});
            buttonVector.push_back(std::make_pair("Not Start", new sf::Sprite(Assets::LOAD_TEXTURE("test3.jpg"))));
            buttonVector.back().second->setOrigin(buttonVector.back().second->getTexture()->getSize().x/2, buttonVector.back().second->getTexture()->getSize().y/2);
            buttonVector.back().second->setPosition({window->getSize().x/2 + 100, window->getSize().y/2});
        };
        void update();
        void draw();
        bool getGameStart();
};
#endif

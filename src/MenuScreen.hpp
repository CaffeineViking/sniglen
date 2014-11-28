#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "utilities/InputHandler.hpp"
#include "utilities/Assets.hpp"
#include "utilities/Button.hpp"

class MenuScreen{
    private:
        InputHandler* input;
        sf::RenderWindow* window;
        std::vector<sf::Sprite*> buttonVector;
        bool gameStart = false;
        bool buttonClicked(const sf::Sprite&);
    public:
        MenuScreen(sf::RenderWindow& screen, InputHandler& handler): window{&screen}, input{&handler} {
            buttonVector.push_back(new sf::Sprite(Assets::LOAD_TEXTURE("test2.jpg")));
            buttonVector.back()->setPosition({window->getSize().x/2, window->getSize().y/2});
            buttonVector.back()->setOrigin(buttonVector.back()->getTexture()->getSize().x/2, buttonVector.back()->getTexture()->getSize().y/2);
        };
        void update();
        void draw();
        bool getGameStart();
};
#endif

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
        enum class MenuState{main = 0, setup, option};
        sf::RenderWindow* window_;
        InputHandler* input_;
        sf::Vector2f windowSize_;
        MenuState state_ = MenuState::main;
        std::vector<std::pair<std::string, sf::Sprite*>> buttonVector_;
        bool gameStart_ = false;
        bool redraw_ = false;
        short unsigned int teamSize_{4};
        short unsigned int playerAmount_{2};
        bool buttonClicked(const sf::Sprite&);
        void createButton(const std::string&, const std::string&, const sf::Vector2f&);
    public:
        MenuScreen(sf::RenderWindow& screen, InputHandler& handler);
        void update();
        void draw();
        bool getGameStart();
        short unsigned int getTeamSize(){return teamSize_;};
        short unsigned int getPlayerAmount(){return playerAmount_;};
};
#endif

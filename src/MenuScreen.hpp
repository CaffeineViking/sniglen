#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include <memory>
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
        std::vector<std::unique_ptr<sf::Text>> textVector_;
        bool gameStart_ = false;
        bool redraw_ = false;
        bool buttonClicked(const sf::Sprite&);
        bool reSpin_ = false;
        int rot;
        float masterVolume_{100};
        float musicVolume_{100};
        float gameVolume_{100};
        float voiceVolume_{100};
        short unsigned int teamSize_{4};
        short unsigned int playerAmount_{2};
        void createButton(const std::string&, const std::string&, const sf::Vector2f&);
        void createText(const std::string&, const std::string&, const sf::Vector2f&, int = 30, const sf::Color& = sf::Color::White, sf::Text::Style = sf::Text::Regular);
    public:
        MenuScreen(sf::RenderWindow& screen, InputHandler& handler);
        void update();
        void draw();
        bool getGameStart();
        short unsigned int getTeamSize(){return teamSize_;};
        short unsigned int getPlayerAmount(){return playerAmount_;};
};
#endif

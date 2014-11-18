#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "entities/Entity.hpp"
#include "environment/Environment.hpp"
#include "utilities/InputHandler.hpp"
#include "utilities/Player.hpp"

sf::Texture loadTexture(const std::string&);
class GameWorld {
    private:
        sf::RenderWindow* gameWindow;
        std::vector<std::unique_ptr<Player>> playerVector;
        Environment environment_;
        InputHandler input;
        sf::View camera_;

    public:
        GameWorld(sf::RenderWindow&);
        void update();
        void draw();
        void keyPressed(const sf::Keyboard::Key & keyEvent);
        void keyReleased(const sf::Keyboard::Key & keyEvent);
        void mousePressed(const sf::Mouse::Button & mouseEvent);
        void mouseReleased(const sf::Mouse::Button & mouseEvent);
};

#endif // GAMEWORLD_HPP

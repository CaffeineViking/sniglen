#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class GameWorld {
    private:
        sf::RenderWindow * gameWindow;
    
    public:
        GameWorld(sf::RenderWindow & window): gameWindow{&window}{}
        void update();
        void keyPressed(const sf::Keyboard::Key & keyEvent);
        void keyReleased(const sf::Keyboard::Key & keyEvent);
        void mousePressed(const sf::Mouse::Button & mouseEvent);
        void mouseReleased(const sf::Mouse::Button & mouseEvent);
};

#endif // GAMEWORLD_HPP

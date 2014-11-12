#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "entities/Entity.hpp"
#include "environment/Environment.hpp"

sf::Texture loadTexture(const std::string&);
class GameWorld {
    private:
        sf::RenderWindow* gameWindow;
        std::vector<Entity*> entVec;
    
    public:
        GameWorld(sf::RenderWindow & window): gameWindow{&window}{
		entVec.push_back(new Unit(loadTexture("share/test.png"), {255,255}, 5, 150));
	}
        void update();
		void draw();
        void keyPressed(const sf::Keyboard::Key & keyEvent);
        void keyReleased(const sf::Keyboard::Key & keyEvent);
        void mousePressed(const sf::Mouse::Button & mouseEvent);
        void mouseReleased(const sf::Mouse::Button & mouseEvent);
	//~GameWorld()
};

#endif // GAMEWORLD_HPP

#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "utilities/Player.hpp"
#include "entities/Entity.hpp"
#include "environment/Environment.hpp"
#include "utilities/InputHandler.hpp"
#include "utilities/Camera.hpp"

class GameWorld {
    private:
        sf::RenderWindow* gameWindow;
        std::vector<std::unique_ptr<Player>> playerVector;
        std::vector<std::unique_ptr<Projectile>> projectileVector;
        Environment environment_;
        InputHandler* input;
        Camera camera_;
        Unit* currentUnit;

    public:
        GameWorld(sf::RenderWindow&, InputHandler&);
        void update();
        void draw();
};

#endif // GAMEWORLD_HPP

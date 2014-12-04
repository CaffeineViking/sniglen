#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "utilities/Assets.hpp"
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
        Environment environment_{9.82, 2560};
        InputHandler* input;
        Camera camera_;
        Unit* currentUnit;
        bool newGame_ = true;
        sf::Sound sound{Assets::LOAD_SOUND("explosion.wav")};

    public:
        GameWorld(sf::RenderWindow&, InputHandler&);
        void update();
        void draw();
        void initiate(short unsigned int players, short unsigned int units);
};

#endif // GAMEWORLD_HPP

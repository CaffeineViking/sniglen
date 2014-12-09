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
        std::vector<std::unique_ptr<sf::Text>> textVector_;
        std::unique_ptr<Environment> environment_;
        InputHandler* input;
        Camera camera_;
        sf::Clock gameTime_;
        sf::Time roundTime_;
        sf::Time delayTime_;
        Unit* currentUnit;
        Entity* cameraTarget_;
        bool newGame_ = true;
        bool shot_ = false;
        float gameVolume_{100};
        float musicVolume_{100};
        sf::Sound explosionSound{Assets::LOAD_SOUND("explosion.wav")};
        void createText(const std::string&, const std::string&, const sf::Vector2f&, int = 30, const sf::Color& = sf::Color::White, sf::Text::Style = sf::Text::Regular);

    public:
        GameWorld(sf::RenderWindow&, InputHandler&);
        void update();
        void draw();
        void initiate(short unsigned int, short unsigned int, float, float);
        void nextRound(std::vector<std::unique_ptr<Player>>::iterator&); // Rickard, du hade rätt!
};

#endif // GAMEWORLD_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"
#include "utilities/Assets.hpp"

GameWorld::GameWorld(sf::RenderWindow& window, InputHandler& inputhandler) : gameWindow{&window}, input{&inputhandler}, camera_{window}  {}

void GameWorld::initiate(short unsigned int players, short unsigned int units){
    environment_ = std::unique_ptr<Environment>{new Environment{9.82, 2560 + (128 * players * units)}};
    environment_->randomizeWind();
    std::cout << environment_->getTerrainSize() << std::endl;

    for(int i{0}; i < players; ++i)
        playerVector.push_back(std::unique_ptr<Player>{new Player{{(unsigned char)Random::GENERATE_MAX(255),(unsigned char)Random::GENERATE_MAX(255),(unsigned char)Random::GENERATE_MAX(255)}}});
    for(int i{0}; i < units; ++i){
        for(auto& i : playerVector)
            i->insertUnit((new Unit{Assets::LOAD_TEXTURE("unit.png"), Assets::LOAD_TEXTURE("testa.png"), {static_cast<float>(Random::GENERATE_MAX(environment_.getTerrainSize())), 180}, 2, 150, i.get()}));
    }
    currentUnit = (*playerVector.begin())->getNextUnit();
}

void GameWorld::update() {
    static auto currentPlayer = playerVector.begin();
    //input.update(gameWindow);
    currentUnit->update(*input, environment_->getTerrain().isColliding(*currentUnit));

    for(std::unique_ptr<Projectile>& projectile : projectileVector){
        projectile->update(*input, environment_->getTerrain().isColliding(*projectile));
        if(environment_->getTerrain().isColliding(*projectile)){
            auto explosion = projectile->explode();
            environment_->getTerrain().destroy(explosion);
            for (auto& player : playerVector) {
                for (Unit* unit : player->getTeam()) {
                    unit->checkExplosion(explosion, projectile->getDamage());
                }
            }
        }
    }

    unsigned iteratedOver {0};
    unsigned removed {0};
    if(!projectileVector.empty()){
        while(iteratedOver + removed < projectileVector.size()){
            if(projectileVector.at(iteratedOver)->isRemoved()){
                projectileVector.at(iteratedOver).swap(projectileVector.at(projectileVector.size()-(++removed)));
            }
            else
                ++iteratedOver;
        }
        projectileVector.erase(projectileVector.begin() + (projectileVector.size()-removed), projectileVector.end());
    }

    if(currentUnit->isShooting()) {
        projectileVector.push_back(std::unique_ptr<Projectile>{
                new Projectile{Assets::LOAD_TEXTURE("bullet.png"), currentUnit->getPosition(), 0.0f, 10, 
                currentUnit->getShootMomentum(*gameWindow), 
                environment_->getWindForce(),
                currentUnit->getShootAngle(), 
                (*currentPlayer)->getCurrentWeapon()
                }
                });
    }
    if(input->isKeyReleased(sf::Keyboard::Key::Return) && currentUnit->inControl()){
        ++currentPlayer;
        if(currentPlayer == playerVector.end())
            currentPlayer = playerVector.begin();
        currentUnit = (*currentPlayer)->getNextUnit();
        environment_->randomizeWind();
    }

    for (auto& player : playerVector) {
        for (Unit* unit : player->getTeam()) {
            if (currentUnit != unit)
                unit->update(InputHandler{}, environment_->getTerrain().isColliding(*unit));
        }
    }

    // The given parameters passed to the camera update function will be used to
    // detemine how the currentUnit will be followed, thus it is also required to pass
    // in environment and the window size to make sure the player is always looking within game bounds.
    camera_.update(*currentUnit, *environment_, gameWindow->getSize().y / 2.0f);
    if (input->isKeyReleased(sf::Keyboard::Key::Tab) || input->isKeyReleased(sf::Keyboard::Key::M)) {
        camera_.toggleZoom(*environment_);
    }
}

void GameWorld::draw() {
    // Draw the terrain to the game window.
    environment_->getTerrain().draw(*gameWindow);

    // Draw all units to the game window.
    for(std::unique_ptr<Player>& player : playerVector){
        for(auto& ent : player->getTeam())
            ent->draw(*gameWindow);
    }

    // Draw all projectiles to the game window.
    for(std::unique_ptr<Projectile>& projectile : projectileVector)
        projectile->draw(*gameWindow);

    // Set the current camera state to be drawn on the game window.
    camera_.draw(*gameWindow);
}

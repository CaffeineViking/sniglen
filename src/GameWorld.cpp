#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"
#include "utilities/Assets.hpp"

GameWorld::GameWorld(sf::RenderWindow& window, InputHandler& inputhandler) : gameWindow{&window}, input{&inputhandler}  {
    camera_ = window.getDefaultView();

    playerVector.push_back(std::unique_ptr<Player>{new Player{{255,0,0}}});
    playerVector.push_back(std::unique_ptr<Player>{new Player{{0,0,255}}});
    for(auto& i : playerVector)
        i->insertUnit((new Unit{Assets::LOAD_TEXTURE("test.png"), Assets::LOAD_TEXTURE("testa.png"), {0, 0}, 2, 150}));
    for(auto& i : playerVector)
        i->insertUnit((new Unit{Assets::LOAD_TEXTURE("test2.jpg"), Assets::LOAD_TEXTURE("testa.png"), {0, 0}, 2, 150}));
    for(auto& i : playerVector)
        i->insertUnit((new Unit{Assets::LOAD_TEXTURE("test3.jpg"), Assets::LOAD_TEXTURE("testa.png"), {0, 0}, 2, 150}));
    for(auto& i : playerVector)
        i->insertUnit((new Unit{Assets::LOAD_TEXTURE("test4.jpg"), Assets::LOAD_TEXTURE("testa.png"), {0, 0}, 2, 150}));
    currentUnit = (*playerVector.begin())->getNextUnit();
}

void GameWorld::update() {
    static auto currentPlayer = playerVector.begin();
    //input.update(gameWindow);
    currentUnit->update(*input, environment_.getTerrain().isColliding(*currentUnit));

    for(std::unique_ptr<Projectile>& projectile : projectileVector){
        projectile->update(*input, environment_.getTerrain().isColliding(*projectile));
        if(environment_.getTerrain().isColliding(*projectile)){
            environment_.getTerrain().destroy(projectile->explode());
        }
    }
    int iteratedOver {0};
    int removed {0};
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

    if(currentUnit->isShooting())
        projectileVector.push_back(std::unique_ptr<Projectile>{new Projectile{Assets::LOAD_TEXTURE("bullet.png"), currentUnit->getPosition(), 0.0f, 10, currentUnit->getShootMomentum(*gameWindow), currentUnit->getShootAngle()}});
    if(input->isKeyReleased(sf::Keyboard::Key::Return) && currentUnit->inControl()){
        ++currentPlayer;
        if(currentPlayer == playerVector.end())
            currentPlayer = playerVector.begin();
        currentUnit = (*currentPlayer)->getNextUnit();
    }

    if(input->mouseReleased())
        environment_.getTerrain().destroy(sf::Mouse::getPosition(*gameWindow) + static_cast<sf::Vector2i>(camera_.getCenter()) - sf::Vector2i{640, 360}, 64.0);
    
    float cameraX {camera_.getCenter().x};
    float cameraY {camera_.getCenter().y};
    if(zoomed){
        cameraX = environment_.getTerrainSize()/2;
        cameraY = 0;
    } else {
        if(currentUnit->getPosition().x - camera_.getSize().x/4 < 0){
            //Check slut vänster
            cameraX = camera_.getSize().x/2;
        }
        else if(currentUnit->getPosition().x + camera_.getSize().x/4 > environment_.getTerrainSize()){
            //Check slut höger
            cameraX = camera_.getSize().x/2 + environment_.getTerrainSize()/2;
        }
        else if(currentUnit->getPosition().x > camera_.getCenter().x + camera_.getSize().x/4){
            //Check går höger
            cameraX = currentUnit->getPosition().x - camera_.getSize().x/4;
        }
        else if(currentUnit->getPosition().x < camera_.getCenter().x - camera_.getSize().x/4){
            //Check går vänster
            cameraX = currentUnit->getPosition().x + camera_.getSize().x/4;
        }
        if(currentUnit->getPosition().y > camera_.getCenter().y + camera_.getSize().y/4){
            cameraY = currentUnit->getPosition().y - camera_.getSize().y/4;
        }
        else if(currentUnit->getPosition().y < camera_.getCenter().y - camera_.getSize().y/4){
            cameraY = currentUnit->getPosition().y + camera_.getSize().y/4;
        }
        else{
            //cameraY = currentUnit->getPosition().y;
        }
    }
    if(cameraY > gameWindow->getSize().y/2)
        cameraY = gameWindow->getSize().y/2;

    camera_.setCenter(cameraX, cameraY);
    if (input->isKeyReleased(sf::Keyboard::Key::Tab)) {
        if (zoomed) {
            camera_.zoom(0.50f);
            zoomed = false;
        } else {
            camera_.zoom(2.0f);
            zoomed = true;
        }
    }
}
void GameWorld::draw() {
    environment_.getTerrain().draw(*gameWindow);
    for(std::unique_ptr<Player>& player : playerVector){
        for(auto ent : player->getTeam())
            ent->draw(*gameWindow);
    }
    for(std::unique_ptr<Projectile>& projectile : projectileVector)
        projectile->draw(*gameWindow);
    gameWindow->setView(camera_);
}

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"
#include "utilities/Assets.hpp"

GameWorld::GameWorld(sf::RenderWindow& window) : gameWindow{&window} {
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
    input.update(gameWindow);
    if (environment_.getTerrain().isColliding(*currentUnit)) {
        currentUnit->collide();
    }
    currentUnit->update(input);

    for(std::unique_ptr<Projectile>& projectile : projectileVector)
        projectile->update(input);
    if(currentUnit->isShooting())
        projectileVector.push_back(std::unique_ptr<Projectile>{new Projectile{Assets::LOAD_TEXTURE("bullet.png"), currentUnit->getPosition(), 0.0f, 10, currentUnit->getShootMomentum(*gameWindow), currentUnit->getShootAngle()}});
    if(input.isKeyReleased(sf::Keyboard::Key::Return) && currentUnit->inControl()){
        ++currentPlayer;
        if(currentPlayer == playerVector.end())
            currentPlayer = playerVector.begin();
        currentUnit = (*currentPlayer)->getNextUnit();
    }

    if(input.mouseReleased())
        environment_.getTerrain().destroy(sf::Mouse::getPosition(*gameWindow) + static_cast<sf::Vector2i>(camera_.getCenter()) - sf::Vector2i{640, 360}, 64.0);
    if(currentUnit->getPosition().x - camera_.getSize().x/2 < 0){
        std::cout << " slkdf" << std::endl;
        camera_.setCenter(camera_.getSize().x/2, currentUnit->getPosition().y);
    }
    else if(currentUnit->getPosition().x + camera_.getSize().x/2 > environment_.getTerrainSize()){
        std::cout << " 222222222222222" << std::endl;
        if(!zoomed){
            std::cout << " weeuuuuweeeuuuooii" << std::endl;
            camera_.setCenter(camera_.getSize().x/2 + environment_.getTerrainSize()/2, currentUnit->getPosition().y);
        }else
             camera_.setCenter(environment_.getTerrainSize()/2, currentUnit->getPosition().y);
    } else { //(currentUnit->getPosition().x > environment_.getTerrainSize() - camera_.getCenter().x){
       camera_.setCenter(currentUnit->getPosition());
       // camera_.setCenter(currentUnit->getPosition().x + currentUnit->getPosition().x - camera_.getCenter().x, currentUnit->getPosition().y);
        std::cout << " inte askjdl " << std::endl;
    }
    std::cout << environment_.getTerrainSize() << std::endl;
    //camera_.setCenter(currentUnit->getPosition());
    if (input.isKeyReleased(sf::Keyboard::Key::Tab)) {
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

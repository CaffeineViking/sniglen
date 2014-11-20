#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"

GameWorld::GameWorld(sf::RenderWindow& window) : gameWindow{&window} {
    camera_ = window.getDefaultView();
    minimap_.setViewport(sf::FloatRect{0.75f, 0.00f, 0.25f, 0.25f});
    minimap_.zoom(4.00);

    playerVector.push_back(std::unique_ptr<Player>{new Player{{255,0,0}}});
    playerVector.push_back(std::unique_ptr<Player>{new Player{{0,0,255}}});
    for(auto& i : playerVector)
        i->insertUnit((new Unit{loadTexture("share/test.png"), loadTexture("share/testa.png"), {255, 255}, 2, 150}));
    for(auto& i : playerVector)
        i->insertUnit((new Unit{loadTexture("share/test2.jpg"), loadTexture("share/testa.png"), {255, 255}, 2, 150}));
    for(auto& i : playerVector)
        i->insertUnit((new Unit{loadTexture("share/test3.jpg"), loadTexture("share/testa.png"), {255, 255}, 2, 150}));
    for(auto& i : playerVector)
        i->insertUnit((new Unit{loadTexture("share/test4.jpg"), loadTexture("share/testa.png"), {255, 255}, 2, 150}));
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
        projectileVector.push_back(std::unique_ptr<Projectile>{new Projectile{loadTexture("share/bullet.png"), currentUnit->getPosition(), 0.0f, 10, currentUnit->getShootMomentum(), currentUnit->getShootAngle()}});
    if(input.isKeyReleased(sf::Keyboard::Key::Return) && currentUnit->inControl()){
        ++currentPlayer;
        if(currentPlayer == playerVector.end())
            currentPlayer = playerVector.begin();
        currentUnit = (*currentPlayer)->getNextUnit();
    }

    if(input.mouseReleased())
        environment_.getTerrain().destroy(sf::Mouse::getPosition(*gameWindow) + static_cast<sf::Vector2i>(camera_.getCenter()) - sf::Vector2i{640, 360}, 64.0);

    camera_.setCenter(currentUnit->getPosition());
}
void GameWorld::draw() {
    environment_.getTerrain().draw(*gameWindow);
    for(std::unique_ptr<Player>& player : playerVector){
        for(auto ent : player->getTeam())
            ent->draw(*gameWindow);
    }
    for(std::unique_ptr<Projectile>& projectile : projectileVector)
        projectile->draw(*gameWindow);
}

void GameWorld::drawCamera() {
    gameWindow->setView(camera_);
    draw();
}

void GameWorld::drawMinimap() {
    gameWindow->setView(minimap_);
    draw();
}

sf::Texture loadTexture(const std::string& fileName) {
    sf::Texture temp;
    temp.loadFromFile(fileName);
    return temp;
}

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"

GameWorld::GameWorld(sf::RenderWindow& window) : gameWindow{&window} {
    camera_ = window.getDefaultView();
    
    playerVector.push_back(std::unique_ptr<Player>{new Player{{255,0,0}}});
    playerVector.push_back(std::unique_ptr<Player>{new Player{{0,0,255}}});
    for(auto& i : playerVector)
        i->insertUnit((new Unit{loadTexture("share/test.png"), {255, 255}, 2, 150}));
    for(auto& i : playerVector)
        i->insertUnit((new Unit{loadTexture("share/test2.jpg"), {255, 255}, 2, 150}));
    for(auto& i : playerVector)
        i->insertUnit((new Unit{loadTexture("share/test3.jpg"), {255, 255}, 2, 150}));
    for(auto& i : playerVector)
        i->insertUnit((new Unit{loadTexture("share/test4.jpg"), {255, 255}, 2, 150}));
    currentUnit = (*playerVector.begin())->getNextUnit();
}

void GameWorld::update() {
    static auto currentPlayer = playerVector.begin();
    input.update(gameWindow);
    if (environment_.getTerrain().isColliding(*currentUnit)) {
        currentUnit->collide();
    }
    currentUnit->update(input);
    if(input.isKeyReleased(sf::Keyboard::Key::Space) && currentUnit->inControl()){
        ++currentPlayer;
        if(currentPlayer == playerVector.end())
            currentPlayer = playerVector.begin();
        currentUnit = (*currentPlayer)->getNextUnit();
    }
}
void GameWorld::draw() {
    gameWindow->setView(camera_);
    environment_.getTerrain().draw(*gameWindow);
    for (std::unique_ptr<Player>& player : playerVector){
        for(auto ent : player->getTeam())
            ent->draw(*gameWindow);
    }
}

void GameWorld::keyPressed(const sf::Keyboard::Key & keyEvent) {
    if (keyEvent == sf::Keyboard::Key::A) {
        camera_.move(-100, 0);
    } else if (keyEvent == sf::Keyboard::Key::D) {
        camera_.move(100, 0);
    }
}

void GameWorld::keyReleased(const sf::Keyboard::Key & keyEvent) {
    if (keyEvent == sf::Keyboard::Key::A)
        std::cout << "bokstaven a var släppt" << std::endl;
}

void GameWorld::mousePressed(const sf::Mouse::Button & mouseEvent) {
    environment_.getTerrain().destroy(sf::Mouse::getPosition(*gameWindow), 32.0);
}

void GameWorld::mouseReleased(const sf::Mouse::Button & mouseEvent) {
}

sf::Texture loadTexture(const std::string& fileName) {
    sf::Texture temp;
    temp.loadFromFile(fileName);
    return temp;
}

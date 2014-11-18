#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"

GameWorld::GameWorld(sf::RenderWindow& window) : gameWindow{&window} {
    camera_ = window.getDefaultView();
    sf::Texture gegelTexture{loadTexture("share/test.png")};
    playerVector.push_back(std::unique_ptr<Player>{new Player{}});
    playerVector.push_back(std::unique_ptr<Player>{new Player{}});
    for(auto& i : playerVector)
        i->insertUnit((new Unit{gegelTexture, {255, 255}, 2, 150}));
}

void GameWorld::update() {
    static auto currentPlayer = playerVector.begin();
    Unit* unit = (*currentPlayer)->getNextUnit();
    input.update(gameWindow);
    if (environment_.getTerrain().isColliding(*unit)) {
        unit->collide();
    }
    unit->update(input);
    if(input.isKeyReleased(sf::Keyboard::Key::Space)){
        std::cout << "plas" << std::endl;
        ++currentPlayer;
        if(currentPlayer == playerVector.end())
            currentPlayer = playerVector.begin();
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
}

void GameWorld::mouseReleased(const sf::Mouse::Button & mouseEvent) {
}

sf::Texture loadTexture(const std::string& fileName) {
    sf::Texture temp;
    temp.loadFromFile(fileName);
    return temp;
}

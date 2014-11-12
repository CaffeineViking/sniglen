#ifndef GAMEWORLD_CPP
#define GAMEWORLD_CPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"

GameWorld::GameWorld(sf::RenderWindow& window) : gameWindow{&window} {
    sf::Texture gegelTexture{loadTexture("share/test.png")};
    entVec.push_back(std::unique_ptr<Entity>{new Unit{gegelTexture, {255, 255}, 2, 150}});
}

void GameWorld::update() {
    for (std::unique_ptr<Entity>& ent : entVec){
        ent->update();
    }
}
void GameWorld::draw() {
    gameWindow->draw(environment_.getTerrain().getSprite());
    for (std::unique_ptr<Entity>& ent : entVec){
        ent->draw(*gameWindow);
    }
}

void GameWorld::keyPressed(const sf::Keyboard::Key & keyEvent) {
    if (keyEvent == sf::Keyboard::Key::A)
        std::cout << "bokstaven a var nedtryckt: " << Random::GENERATE_MAX(30) << std::endl;
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

#endif

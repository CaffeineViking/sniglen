#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"

GameWorld::GameWorld(sf::RenderWindow& window) : gameWindow{&window} {
    camera_ = window.getDefaultView();
    sf::Texture gegelTexture{loadTexture("share/test.png")};
    entVec.push_back(std::unique_ptr<Entity>{new Unit{gegelTexture, {255, 255}, 2, 150}});
}

void GameWorld::update() {
    input.update(gameWindow);
    for (std::unique_ptr<Entity>& ent : entVec) {
        if (environment_.getTerrain().isColliding(*ent)) {
            //std::cout << "Colliding" << std::endl;
            ent->collide();
        }
        ent->update(input);
    }
}
void GameWorld::draw() {
    gameWindow->setView(camera_);
    environment_.getTerrain().draw(*gameWindow);
    for (std::unique_ptr<Entity>& ent : entVec){
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

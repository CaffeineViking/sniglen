#ifndef GAMEWORLD_CPP
#define GAMEWORLD_CPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"

void GameWorld::update(){
}

void GameWorld::keyPressed(const sf::Keyboard::Key & keyEvent){
    if(keyEvent == sf::Keyboard::Key::A)
        std::cout << "bokstaven a var nedtryckt: " << Random::GENERATE_MAX(30) << std::endl;
}

void GameWorld::keyReleased(const sf::Keyboard::Key & keyEvent){
    if(keyEvent == sf::Keyboard::Key::A)
        std::cout << "bokstaven a var släppt" << std::endl; 
}

void GameWorld::mousePressed(const sf::Mouse::Button & mouseEvent){
}

void GameWorld::mouseReleased(const sf::Mouse::Button & mouseEvent){
}

#endif

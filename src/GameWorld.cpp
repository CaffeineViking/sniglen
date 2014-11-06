#ifndef GAMEWORLD_CPP
#define GAMEWORLD_CPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"

void GameWorld::update(){
	for(Entity* ent : entVec){
		ent->update();
	}
}
void GameWorld::draw(){
	for(Entity* ent : entVec){
		ent->draw(*gameWindow);
	}
}

void GameWorld::keyPressed(const sf::Keyboard::Key & keyEvent){
    if(keyEvent == sf::Keyboard::Key::A)
        std::cout << "bokstaven a var nedtryckt" << std::endl;
}

void GameWorld::keyReleased(const sf::Keyboard::Key & keyEvent){
    if(keyEvent == sf::Keyboard::Key::A)
        std::cout << "bokstaven a var släppt" << std::endl; 
}

void GameWorld::mousePressed(const sf::Mouse::Button & mouseEvent){
    
}

void GameWorld::mouseReleased(const sf::Mouse::Button & mouseEvent){
    
}

sf::Texture loadTexture(const std::string& fileName){
    sf::Texture temp;
    temp.loadFromFile(fileName);
    return temp;
}
#endif

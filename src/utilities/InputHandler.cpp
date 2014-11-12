#ifndef INPUTHANDLER_CPP
#define INPUTHANDLER_CPP

#include "InputHandler.hpp"

void InputHandler::keyboardUpdate(){
    releasedKeys_.clear();
    if (pressedKeys_.find(sf::Keyboard::Key::Up) != pressedKeys_.end()){
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ //500 To be changed to variable y coords
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
    }
}
bool isKeyPressed(sf::Keyboard::Key key){
    return true;
}
#endif

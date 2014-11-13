#ifndef INPUTHANDLER_CPP
#define INPUTHANDLER_CPP

#include "InputHandler.hpp"

void InputHandler::keyboardUpdate(){
    releasedKeys_.clear();
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        pressedKeys_.erase(sf::Keyboard::Up);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && pressedKeys_.find(sf::Keyboard::Key::Up) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Up);
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        pressedKeys_.erase(sf::Keyboard::Down);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && pressedKeys_.find(sf::Keyboard::Key::Down) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Down);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Down);
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        pressedKeys_.erase(sf::Keyboard::Left);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pressedKeys_.find(sf::Keyboard::Key::Left) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Left);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Left);
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        pressedKeys_.erase(sf::Keyboard::Right);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pressedKeys_.find(sf::Keyboard::Key::Right) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Right);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Right);
    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        pressedKeys_.erase(sf::Keyboard::Space);
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && pressedKeys_.find(sf::Keyboard::Key::Space) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Space);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Space);
    }
}
bool InputHandler::isKeyPressed(sf::Keyboard::Key key) const{
    return pressedKeys_.find(key) != pressedKeys_.end();
}
void InputHandler::mouseUpdate(sf::RenderWindow* window){
    mousePos_ = sf::Mouse::getPosition(*window);
    mouseReleased_ = false;
    if(mouseClicked_ && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        mouseReleased_ = true;
    mouseClicked_ = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}
#endif

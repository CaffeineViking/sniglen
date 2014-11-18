#ifndef INPUTHANDLER_CPP
#define INPUTHANDLER_CPP

#include "InputHandler.hpp"

void InputHandler::keyboardUpdate(){
    releasedKeys_.clear();

    // Up arrow
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && pressedKeys_.find(sf::Keyboard::Key::Up) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Up);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        pressedKeys_.erase(sf::Keyboard::Key::Up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Up);
    }

    // Down arrow
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && pressedKeys_.find(sf::Keyboard::Key::Down) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Down);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        pressedKeys_.erase(sf::Keyboard::Key::Down);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Down);
    }

    // Left arrow
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && pressedKeys_.find(sf::Keyboard::Key::Left) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Left);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
        pressedKeys_.erase(sf::Keyboard::Key::Left);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Left);
    }

    // Right arrow
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && pressedKeys_.find(sf::Keyboard::Key::Right) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Right);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        pressedKeys_.erase(sf::Keyboard::Key::Right);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Right);
    }

    // Space
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && pressedKeys_.find(sf::Keyboard::Key::Space) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Space);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        pressedKeys_.erase(sf::Keyboard::Space);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Space);
    }

    // Backspace
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace) && pressedKeys_.find(sf::Keyboard::Key::BackSpace) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::BackSpace);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace)){
        pressedKeys_.erase(sf::Keyboard::Key::BackSpace);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::BackSpace);
    }

    // Return
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && pressedKeys_.find(sf::Keyboard::Key::Return) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Return);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){
        pressedKeys_.erase(sf::Keyboard::Key::Return);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Return);
    }
}
bool InputHandler::isKeyPressed(sf::Keyboard::Key key) const{
    return pressedKeys_.find(key) != pressedKeys_.end();
}
bool InputHandler::isKeyReleased(sf::Keyboard::Key key) const{
    return releasedKeys_.find(key) != releasedKeys_.end();
}
void InputHandler::mouseUpdate(sf::RenderWindow* window){
    mousePos_ = sf::Mouse::getPosition(*window);
    mouseReleased_ = false;
    if(mouseClicked_ && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        mouseReleased_ = true;
    mouseClicked_ = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}
#endif

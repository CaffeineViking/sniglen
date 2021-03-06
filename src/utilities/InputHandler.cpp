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

    // Tab
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab) && pressedKeys_.find(sf::Keyboard::Key::Tab) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Tab);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)){
        pressedKeys_.erase(sf::Keyboard::Key::Tab);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Tab);
    }

    // Escape
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && pressedKeys_.find(sf::Keyboard::Key::Escape) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Escape);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
        pressedKeys_.erase(sf::Keyboard::Key::Escape);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Escape);
    }

    // Num1
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && pressedKeys_.find(sf::Keyboard::Key::Num1) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Num1);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)){
        pressedKeys_.erase(sf::Keyboard::Key::Num1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Num1);
    }
    //
    // Num2
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && pressedKeys_.find(sf::Keyboard::Key::Num2) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Num2);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)){
        pressedKeys_.erase(sf::Keyboard::Key::Num2);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Num2);
    }
    // Num3
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) && pressedKeys_.find(sf::Keyboard::Key::Num3) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Num3);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)){
        pressedKeys_.erase(sf::Keyboard::Key::Num3);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Num3);
    }
    // Delete
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete) && pressedKeys_.find(sf::Keyboard::Key::Delete) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::Delete);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete)){
        pressedKeys_.erase(sf::Keyboard::Key::Delete);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Delete)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::Delete);
    }
    // F
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) && pressedKeys_.find(sf::Keyboard::Key::F) != pressedKeys_.end()){
        releasedKeys_.insert(sf::Keyboard::Key::F);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)){
        pressedKeys_.erase(sf::Keyboard::Key::F);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)){ //500 To be changed to variable y coords
        pressedKeys_.insert(sf::Keyboard::Key::F);
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

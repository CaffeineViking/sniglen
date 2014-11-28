#include "MenuScreen.hpp"

void MenuScreen::update(){
    if(input->mouseReleased()){
       for(sf::Sprite* button : buttonVector){
           if(buttonClicked(*button))
               gameStart = true;
       }
    }
}
void MenuScreen::draw(){
    for(sf::Sprite* button : buttonVector){
        window->draw(*button);
    }
}
bool MenuScreen::buttonClicked(const sf::Sprite& sprite){
    if(input->mousePosition().x > sprite.getPosition().x - sprite.getTexture()->getSize().x/2 &&
       input->mousePosition().x < sprite.getPosition().x + sprite.getTexture()->getSize().x/2 &&
       input->mousePosition().y > sprite.getPosition().y - sprite.getTexture()->getSize().y/2 &&
       input->mousePosition().y < sprite.getPosition().y + sprite.getTexture()->getSize().y/2)
        return true;
    return false;
}
bool MenuScreen::getGameStart(){
    bool temp = gameStart;
    gameStart = false;
    return temp;
}

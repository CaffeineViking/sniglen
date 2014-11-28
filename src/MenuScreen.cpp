#include "MenuScreen.hpp"

MenuScreen::MenuScreen(sf::RenderWindow& screen, InputHandler& handler): window{&screen}, input{&handler} {
    buttonVector.push_back(std::make_pair("Start", new sf::Sprite(Assets::LOAD_TEXTURE("test2.jpg"))));
    buttonVector.back().second->setOrigin(buttonVector.back().second->getTexture()->getSize().x/2, buttonVector.back().second->getTexture()->getSize().y/2);
    buttonVector.back().second->setPosition({(float)window->getSize().x/2, (float)window->getSize().y/2});
    buttonVector.push_back(std::make_pair("Not Start", new sf::Sprite(Assets::LOAD_TEXTURE("test3.jpg"))));
    buttonVector.back().second->setOrigin(buttonVector.back().second->getTexture()->getSize().x/2, buttonVector.back().second->getTexture()->getSize().y/2);
    buttonVector.back().second->setPosition({(float)window->getSize().x/2 + 100, (float)window->getSize().y/2});
}
void MenuScreen::update(){
    if(input->mouseReleased()){
        for(std::pair<std::string, sf::Sprite*> button : buttonVector){
            if(buttonClicked(*button.second)){
                if(button.first == "Start")
                    gameStart = true;
            }
        }
    }
}
void MenuScreen::draw(){
    for(std::pair<std::string, sf::Sprite*> button : buttonVector){
        window->draw(*button.second);
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

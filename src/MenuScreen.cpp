#include "MenuScreen.hpp"

MenuScreen::MenuScreen(sf::RenderWindow& screen, InputHandler& handler): window_{&screen}, input_{&handler} {
    windowSize_ = (sf::Vector2f)window_->getSize();
    createButton("test2.png", "Setup", {windowSize_.x/2, windowSize_.y/2});
    createButton("test3.png", "Options", {windowSize_.x/2 + 100, windowSize_.y/2});
    createButton("test.png", "Exit", {windowSize_.x/2, windowSize_.y/2 + 100});
}

void MenuScreen::update(){
    if(redraw_){
        if(state_ == MenuState::main){
            buttonVector_.clear();
            createButton("test2.png", "Setup", {windowSize_.x/2, windowSize_.y/2});
            createButton("test3.png", "Options", {windowSize_.x/2 + 100, windowSize_.y/2});
            createButton("test.png", "Exit", {windowSize_.x/2, windowSize_.y/2 + 100});
        }
        else if(state_ == MenuState::setup){
            buttonVector_.clear();
            createButton("incTeam.png", "incTeam", {windowSize_.x/2 - 50, windowSize_.y/2});
            createButton("bullet.png", "decTeam", {windowSize_.x/2 + 50, windowSize_.y/2});
            createButton("incPlayers.png", "incPlayers", {windowSize_.x/2 - 50, windowSize_.y/2 - 50});
            createButton("decPlayers.png", "decPlayers", {windowSize_.x/2 + 50, windowSize_.y/2 - 50});
            createButton("StartGame.png", "StartGame", {windowSize_.x/2, windowSize_.y/2 + 100});
            createButton("test2.png", "Back", {windowSize_.x/2, windowSize_.y-100});
        }
        else if(state_ == MenuState::option){
            buttonVector_.clear();
            createButton("test2.png", "Back", {windowSize_.x/2, windowSize_.y-100});
        } else {
        }
        redraw_ = false;
    }
    if(input_->mouseReleased()){
        for(std::pair<std::string, sf::Sprite*> button : buttonVector_){
            if(buttonClicked(*button.second)){
                if(button.first == "StartGame")
                    gameStart_ = true;
                if(button.first == "incTeam" && teamSize_ < 5)
                    ++teamSize_;
                if(button.first == "decTeam" && teamSize_ > 1)
                    --teamSize_;
                if(button.first == "incPlayers" && playerAmount_ < 5)
                    ++playerAmount_;
                if(button.first == "decPlayers" && playerAmount_ > 1)
                    --playerAmount_;
                if(button.first == "Setup")
                    state_ = MenuState::setup;
                if(button.first == "Options")
                    state_ = MenuState::option;
                if(button.first == "Back")
                    state_ = MenuState::main;
                if(button.first == "Exit")
                    window_->close();

            }
            redraw_ = true;
        }
    }
}
void MenuScreen::draw(){
    for(std::pair<std::string, sf::Sprite*> button : buttonVector_){
        window_->draw(*button.second);
    }
}

void MenuScreen::createButton(const std::string& filename, const std::string& label, const sf::Vector2f& position){
    // Create button
    buttonVector_.push_back(std::make_pair(label, new sf::Sprite(Assets::LOAD_TEXTURE(filename))));
    // Set origin to middle
    buttonVector_.back().second->setOrigin(buttonVector_.back().second->getTexture()->getSize().x/2, buttonVector_.back().second->getTexture()->getSize().y/2);
    // Set position
    buttonVector_.back().second->setPosition(position);
}

bool MenuScreen::buttonClicked(const sf::Sprite& sprite){
    if(input_->mousePosition().x > sprite.getPosition().x - sprite.getTexture()->getSize().x/2 &&
       input_->mousePosition().x < sprite.getPosition().x + sprite.getTexture()->getSize().x/2 &&
       input_->mousePosition().y > sprite.getPosition().y - sprite.getTexture()->getSize().y/2 &&
       input_->mousePosition().y < sprite.getPosition().y + sprite.getTexture()->getSize().y/2)
        return true;
    return false;
}
bool MenuScreen::getGameStart(){
    bool temp = gameStart_;
    gameStart_ = false;
    return temp;
}

#include "MenuScreen.hpp"
#include <string>
#include <iostream>
#include "utilities/to_string.hpp"

MenuScreen::MenuScreen(sf::RenderWindow& screen, InputHandler& handler): window_{&screen}, input_{&handler} {
    createText("™Sniglen: the Game: the Movie: Reloaded: Limited Limited Edition!™", "BebasNeue.otf", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 - 150});
    createButton("setupGame.png", "Setup", {Assets::WINDOW_SIZE.x/2 - 100, Assets::WINDOW_SIZE.y/2});
    createButton("options.png", "Options", {Assets::WINDOW_SIZE.x/2 + 100, Assets::WINDOW_SIZE.y/2});
    createButton("quit.png", "Exit", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 + 100});
}

void MenuScreen::update(){
    if(redraw_){
        buttonVector_.clear();
        textVector_.clear();
        if(state_ == MenuState::main){
            createText("™Sniglen: the Game: the Movie: Reloaded: Limited Limited Edition!™", "BebasNeue.otf", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 - 150});
            createButton("setupGame.png", "Setup", {Assets::WINDOW_SIZE.x/2 - 100, Assets::WINDOW_SIZE.y/2});
            createButton("options.png", "Options", {Assets::WINDOW_SIZE.x/2 + 100, Assets::WINDOW_SIZE.y/2});
            createButton("est", "Egg", {50, 50});
            createButton("est", "Stahp", {600, 600});
            createButton("quit.png", "Exit", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 + 100});
        }
        else if(state_ == MenuState::setup){
            createText(to_string(teamSize_), "BebasNeue.otf", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 + 40}, 30);
            createText(to_string(playerAmount_), "BebasNeue.otf", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 - 60}, 30);
            createButton("incUnit.png", "incTeam", {Assets::WINDOW_SIZE.x/2 + 100, Assets::WINDOW_SIZE.y/2 + 50});
            createButton("decUnit.png", "decTeam", {Assets::WINDOW_SIZE.x/2 - 100, Assets::WINDOW_SIZE.y/2 + 50});
            createButton("incPlayers.png", "incPlayers", {Assets::WINDOW_SIZE.x/2 + 100, Assets::WINDOW_SIZE.y/2 - 50});
            createButton("decPlayers.png", "decPlayers", {Assets::WINDOW_SIZE.x/2 - 100, Assets::WINDOW_SIZE.y/2 - 50});
            createButton("startGame.png", "StartGame", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 + 175});
            createButton("back.png", "Back", {Assets::WINDOW_SIZE.x/2 + 400, Assets::WINDOW_SIZE.y-100});
            
            //Instructions on the setup
            createAlignLeftText("Controls:", "BebasNeue.otf", {150, 50}, 35);
            createAlignLeftText("Arrow right/left  -  Move", "BebasNeue.otf", {100, 85});
            createAlignLeftText("Arrow up/down  -  Aim", "BebasNeue.otf", {100, 110});
            createAlignLeftText("Key 1  -  Bazooka, medium damage, medium explosion", "BebasNeue.otf", {100, 135});
            createAlignLeftText("Key 2  -  Mini Bazooka, high damage, mini explosion", "BebasNeue.otf", {100, 160});
            createAlignLeftText("Key 3  -  Nuke, low damage, so biggi explosion!!", "BebasNeue.otf", {100, 185});
            createAlignLeftText("Space  -  Shoot", "BebasNeue.otf", {100, 210});
            createAlignLeftText("Backspace  -  Jump", "BebasNeue.otf", {100, 235});
            createAlignLeftText("Delete  -  Back to menu", "BebasNeue.otf", {100, 260});
            createAlignLeftText("Escape  -  Turn off game", "BebasNeue.otf", {100, 285});
        }
        else if(state_ == MenuState::option){
            createText("Game Volume", "BebasNeue.otf", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 - 70});
            createText(to_string((int)gameVolume_)+ " %", "BebasNeue.otf", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 - 10});
            createButton("increase.png", "incGameVol", {Assets::WINDOW_SIZE.x/2 + 125, Assets::WINDOW_SIZE.y/2});
            createButton("decrease.png", "decGameVol", {Assets::WINDOW_SIZE.x/2 - 125, Assets::WINDOW_SIZE.y/2});
            createText("Music Volume", "BebasNeue.otf", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 + 55});
            createText(to_string((int)musicVolume_)+ " %", "BebasNeue.otf", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y/2 + 115});
            createButton("increase.png", "incMusic", {Assets::WINDOW_SIZE.x/2 + 125, Assets::WINDOW_SIZE.y/2 + 125});
            createButton("decrease.png", "decMusic", {Assets::WINDOW_SIZE.x/2 - 125, Assets::WINDOW_SIZE.y/2 + 125});
            createButton("back.png", "Back", {Assets::WINDOW_SIZE.x/2, Assets::WINDOW_SIZE.y-100});
        }
        redraw_ = false;
    }
    if(input_->mouseReleased()){
        for(std::pair<std::string, sf::Sprite*> button : buttonVector_){
            if(buttonClicked(*button.second)){
                if(button.first == "Setup")
                    state_ = MenuState::setup;
                if(button.first == "StartGame")
                    gameStart_ = true;
                if(button.first == "incTeam" && teamSize_ < 5)
                    ++teamSize_;
                if(button.first == "decTeam" && teamSize_ > 1)
                    --teamSize_;
                if(button.first == "incPlayers" && playerAmount_ < 5)
                    ++playerAmount_;
                if(button.first == "decPlayers" && playerAmount_ > 2)
                    --playerAmount_;
                if(button.first == "Options")
                    state_ = MenuState::option;
                if(button.first == "incGameVol" && gameVolume_ < 100)
                    gameVolume_ = gameVolume_ + 10;
                if(button.first == "decGameVol" && gameVolume_ > 0)
                    gameVolume_ = gameVolume_ - 10;
                if(button.first == "incMusic" && musicVolume_ < 100)
                    musicVolume_ = musicVolume_ + 10;
                if(button.first == "decMusic" && musicVolume_ > 0)
                    musicVolume_ = musicVolume_ - 10;
                if(button.first == "Back")
                    state_ = MenuState::main;
                if(button.first == "Egg"){
                    egg = true;
                    stahp = false;
                }
                if(button.first == "Stahp"){
                    stahp = true;
                    egg = false;
                }
                if(button.first == "Exit")
                    window_->close();

            }
            redraw_ = true;
        }
    }
    static float tempF = 0;
    for(std::unique_ptr<sf::Text>& text : textVector_){
        if(egg){
            text->setRotation(text->getRotation() + 10.0f);
            tempF = text->getRotation();
        }
        if(stahp){
            text->setRotation(tempF);
        } 
        /*else{
            text->setRotation(1.0f);
        }*/
    }
}
void MenuScreen::draw(){
    for(std::unique_ptr<sf::Text>& text : textVector_){
        window_->draw(*text);
    }
    for(std::pair<std::string, sf::Sprite*> button : buttonVector_){
        window_->draw(*button.second);
    }
}

void MenuScreen::createButton(const std::string& filename, const std::string& label, const sf::Vector2f& position){
    // Create button
    if(filename == "est"){
        static sf::Texture est;
        est.create(50,50);
        buttonVector_.push_back(std::make_pair(label, new sf::Sprite(est)));
    }
    else
        buttonVector_.push_back(std::make_pair(label, new sf::Sprite(Assets::LOAD_TEXTURE(filename))));
    // Set origin to middle
    buttonVector_.back().second->setOrigin(buttonVector_.back().second->getTexture()->getSize().x/2, buttonVector_.back().second->getTexture()->getSize().y/2);
    // Set position
    buttonVector_.back().second->setPosition(position);
}

void MenuScreen::createText(const std::string& text, const std::string& font, const sf::Vector2f& position, int size, const sf::Color& color, sf::Text::Style style){
    textVector_.push_back(std::move(std::unique_ptr<sf::Text>{new sf::Text(text, Assets::LOAD_FONT(font), size)}));
    textVector_.back()->setOrigin({textVector_.back()->getLocalBounds().width/2, textVector_.back()->getLocalBounds().height/2});
    textVector_.back()->setPosition(position);
    textVector_.back()->setStyle(style);
    textVector_.back()->setColor(color);
}


void MenuScreen::createAlignLeftText(const std::string& text, const std::string& font, const sf::Vector2f& position, int size, const sf::Color& color, sf::Text::Style style){
    createText(text, font, position, size, color, style);
    textVector_.back()->setOrigin({0, textVector_.back()->getLocalBounds().height/2});
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

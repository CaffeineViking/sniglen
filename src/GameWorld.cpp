#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "GameWorld.hpp"
#include "utilities/Random.hpp"
#include "utilities/Assets.hpp"
#include "utilities/to_string.hpp"

GameWorld::GameWorld(sf::RenderWindow& window, InputHandler& inputhandler) : gameWindow{&window}, input{&inputhandler}, camera_{window}  {}

void GameWorld::initiate(short unsigned int players, short unsigned int units, float gameVolume, float musicVolume){
    roundTime_ = gameTime_.getElapsedTime();
    delayTime_ = gameTime_.getElapsedTime();
    textVector_.clear();
    playerVector.clear();
    projectileVector.clear();
    environment_ = std::unique_ptr<Environment>{new Environment{9.82, static_cast<unsigned>(2560 + (128 * players * units))}};
    environment_->randomizeWind();

    gameVolume_ = gameVolume;
    musicVolume_ = musicVolume;
    for(int i{0}; i < players; ++i)
        playerVector.push_back(std::unique_ptr<Player>{new Player{{(unsigned char)Random::GENERATE_MAX(255),(unsigned char)Random::GENERATE_MAX(255),(unsigned char)Random::GENERATE_MAX(255)}}});
    for(int i{0}; i < units; ++i){
        for(auto& i : playerVector){
            i->insertUnit(new Unit{Assets::LOAD_TEXTURE("unit.png"), Assets::LOAD_TEXTURE("crosshair.png"), {static_cast<float>(Random::GENERATE_MAX(environment_->getTerrainSize())), 180}, 1, 150, i.get()});
        i->getTeam().back()->disableCrosshair();
        }
    }

    explosionSound.setVolume(gameVolume_);
    currentUnit = (*playerVector.begin())->getNextUnit();
    currentUnit->enableCrosshair();
    cameraTarget_ = currentUnit;
}

void GameWorld::nextRound(std::vector<std::unique_ptr<Player>>::iterator& currentPlayer) {
    shot_ = false;
    std::vector<std::unique_ptr<Player>>::iterator tempPlayer = currentPlayer;
    do{
        ++currentPlayer;
        if(currentPlayer == playerVector.end())
            currentPlayer = playerVector.begin();
        if(tempPlayer == currentPlayer)
            win();
    }while ((*currentPlayer)->isTeamDead());
    currentUnit = (*currentPlayer)->getNextUnit(); 
    /*if(!(*currentPlayer)->isTeamDead())*/ currentUnit->enableCrosshair();
    currentUnit->noShooting();

    for (auto& player : playerVector) {
        for (auto& unit : player->getTeam()) {
            if (currentUnit != unit)
                unit->disableCrosshair();
        }
    }

    int spawnCrate{Random::GENERATE_MINMAX(1, 4)};
    if (spawnCrate == 1) {
        crateVector.push_back(std::unique_ptr<HealthCrate>{new HealthCrate{{static_cast<float>(Random::GENERATE_MAX(environment_->getTerrainSize())), 10}}});
    } else if (spawnCrate == 2) {
        crateVector.push_back(std::unique_ptr<WeaponCrate>{new WeaponCrate{{static_cast<float>(Random::GENERATE_MAX(environment_->getTerrainSize())), 10}}});
    }

    cameraTarget_ = currentUnit;
    environment_->randomizeWind();
    roundTime_ = gameTime_.getElapsedTime();
}

void GameWorld::update() {
    textVector_.clear();
    std::string windForceText;
    float tempWind = environment_->getWindForce();
    if(tempWind < 0){
        while(tempWind + 0.1 < 0){
            windForceText += "<";
            tempWind += 0.1;
        }
    }
    else if(tempWind - 0.1 > 0){
        while(tempWind - 0.1 > 0){
            windForceText += ">";
            tempWind -= 0.1;
        }
    }

    createText(windForceText, "BebasNeue.otf", {camera_.getPosition().x, camera_.getPosition().y - Assets::WINDOW_SIZE.y / 2 + 50}, 150);
    static auto currentPlayer = playerVector.begin();
    if (!currentUnit->isDead()) {
        currentUnit->update(*input, environment_->getTerrain().isColliding(*currentUnit), *environment_);
    } else {
        nextRound(currentPlayer);
    }

    createText((*currentPlayer)->getCurrentWeaponString() + ": " + to_string((*currentPlayer)->getCurrentWeaponAmmo()), "BebasNeue.otf", {camera_.getPosition().x, camera_.getPosition().y - Assets::WINDOW_SIZE.y / 2 + 175}, 32);

    unsigned iteratedOver {0};
    unsigned removed {0};
    if(!projectileVector.empty()){
        while(iteratedOver + removed < projectileVector.size()){
            if(projectileVector.at(iteratedOver)->isRemoved()){
                // cameraTarget_ = currentUnit;
                projectileVector.at(iteratedOver) = nullptr;
                projectileVector.at(iteratedOver).swap(projectileVector.at(projectileVector.size()-(++removed)));
            }
            else
                ++iteratedOver;
        }
        projectileVector.erase(projectileVector.begin() + (projectileVector.size()-removed), projectileVector.end());
    }

    if(currentUnit->isShooting() && !shot_ && (*currentPlayer)->getCurrentWeaponAmmo() > 0) {
        shot_ = true;
        currentUnit->disableCrosshair();
        projectileVector.push_back(std::move(std::unique_ptr<Projectile>{
                    new Projectile{Assets::LOAD_TEXTURE("bullet.png"), currentUnit->getCrosshairPosition(), 0.0f, 10, 
                    currentUnit->getShootMomentum(), 
                    environment_->getWindForce(),
                    currentUnit->getShootAngle(), 
                    (*currentPlayer)->getCurrentWeapon().get()
                    }
                    }));
        (*currentPlayer)->useCurrentWeapon();

        // nextRound(currentPlayer);
        delayTime_ = gameTime_.getElapsedTime();
        cameraTarget_ = projectileVector.back().get();
    }

    for(std::unique_ptr<Projectile>& projectile : projectileVector){
        projectile->update(*input, environment_->getTerrain().isColliding(*projectile), *environment_);
        if(environment_->getTerrain().isColliding(*projectile)){
            auto explosion = projectile->explode();
            environment_->getTerrain().destroy(explosion);
            explosionSound.play();

            bool hit{false};
            for (auto& player : playerVector) {
                for (auto& unit : player->getTeam()) {
                    if (unit->checkExplosion(explosion, projectile->getDamage()) && unit != currentUnit) {
                        cameraTarget_ = unit;
                        hit = true;
                    }
                }
            }

            if (!hit) cameraTarget_ = currentUnit;
        }
        else{
            for (auto& player : playerVector) {
                for (auto& unit : player->getTeam()) {
                    if (projectile->isColliding(*unit)) {
                        auto explosion = projectile->explode();
                        environment_->getTerrain().destroy(explosion);
                        explosionSound.play();

                        bool hit{false};
                        for (auto& player : playerVector) {
                            for (auto& unit : player->getTeam()) {
                                if (unit->checkExplosion(explosion, projectile->getDamage()) && unit != currentUnit) {
                                    cameraTarget_ = unit;
                                    hit = true;
                                }
                            }
                        }
                        if (!hit) cameraTarget_ = currentUnit;
                    }
                }
            }
        }
    }

    static const float ROUND_TIME{15.0f};
    static const float DELAY_TIME{3.0f};
    float realRoundTime{(gameTime_.getElapsedTime() - roundTime_).asSeconds()};
    float realDelayTime{(gameTime_.getElapsedTime() - delayTime_).asSeconds()};
    if((realRoundTime> ROUND_TIME && currentUnit->inControl()) ||
        (shot_ && realDelayTime > DELAY_TIME)){
        nextRound(currentPlayer);
    }

    if (!shot_)
        createText(to_string(static_cast<unsigned>(ROUND_TIME -  realRoundTime)), "BebasNeue.otf", {camera_.getPosition().x, camera_.getPosition().y - Assets::WINDOW_SIZE.y / 2 + 25}, 48);
    else
        createText(to_string(static_cast<unsigned>(DELAY_TIME - realDelayTime)), "BebasNeue.otf", {camera_.getPosition().x, camera_.getPosition().y - Assets::WINDOW_SIZE.y / 2 + 25}, 48);

    for (auto& player : playerVector) {
        bool removed{false};
        for (auto& unit : player->getTeam()) {
            if (currentUnit != unit)
                unit->update(environment_->getTerrain().isColliding(*unit), *environment_);

            if (unit->getPos().y > gameWindow->getSize().y + unit->getSprite().getTexture()->getSize().y) {
                removed = true;
                unit->remove();

                if (unit == currentUnit)
                    nextRound(currentPlayer);
            }
        }

        if (removed)
            player->removeUnits();
    }

    for (auto& crate : crateVector) {
        crate->update(InputHandler{}, environment_->getTerrain().isColliding(*crate), *environment_);
        for (auto& player : playerVector) {
            for (auto& unit : player->getTeam()) {
                if (crate->isColliding(*unit)) {
                    if (HealthCrate* healthCrate = dynamic_cast<HealthCrate*>(crate.get())) {
                        unit->giveHealth(std::ceil(healthCrate->pickUp()));
                    } else if (WeaponCrate* weaponCrate = dynamic_cast<WeaponCrate*>(crate.get())) {
                        auto weapon = weaponCrate->pickUp();
                        player->increaseAmmo(weapon.first, weapon.second);
                    }
                }
            }
        }
    }

    iteratedOver = 0;
    removed = 0;
    if(!crateVector.empty()){
        while(iteratedOver + removed < crateVector.size()){
            if(crateVector.at(iteratedOver)->isRemoved()){
                crateVector.at(iteratedOver) = nullptr;
                crateVector.at(iteratedOver).swap(crateVector.at(crateVector.size()-(++removed)));
            }
            else
                ++iteratedOver;
        }
        crateVector.erase(crateVector.begin() + (crateVector.size()-removed), crateVector.end());
    }

    if (input->isKeyPressed(sf::Keyboard::Key::Left) ||
            input->isKeyPressed(sf::Keyboard::Key::Right) ||
            input->isKeyPressed(sf::Keyboard::Key::BackSpace)) {
        cameraTarget_ = currentUnit;
    }

    // The given parameters passed to the camera update function will be used to
    // detemine how the currentUnit will be followed, thus it is also required to pass
    // in environment and the window size to make sure the player is always looking within game bounds.
    if (cameraTarget_ == nullptr) cameraTarget_ = currentUnit;
    camera_.update(cameraTarget_, *environment_, gameWindow->getSize().y / 2.0f);
    if (input->isKeyReleased(sf::Keyboard::Key::Tab) || input->isKeyReleased(sf::Keyboard::Key::M)) {
        camera_.toggleZoom(*environment_);
    }
}

void GameWorld::draw() {
    // Draw the terrain to the game window.
    environment_->getTerrain().draw(*gameWindow);

    for(std::unique_ptr<sf::Text>& text : textVector_)
        gameWindow->draw(*text);
    // Draw all units to the game window.
    for(std::unique_ptr<Player>& player : playerVector){
        for(auto& ent : player->getTeam())
            ent->draw(*gameWindow);
    }

    // Draw all crates to the game window.
    for(std::unique_ptr<Crate>& crate : crateVector)
        crate->draw(*gameWindow);

    // Draw all projectiles to the game window.
    for(std::unique_ptr<Projectile>& projectile : projectileVector)
        projectile->draw(*gameWindow);

    // Set the current camera state to be drawn on the game window.
    camera_.draw(*gameWindow);
}

void GameWorld::win(){
    textVector_.clear();
    for(size_t i = 0; i < playerVector.size(); ++i){
        if(!playerVector[i]->isTeamDead()){
            createText("Player " + to_string(i + 1) + " wins! \n Click the mouse to continue.", "BebasNeue.otf", {camera_.getPosition().x, camera_.getPosition().y - Assets::WINDOW_SIZE.y / 2 + 150}, 32);
            gameWindow->clear({0,255,0});
        }
    }
    if(textVector_.empty()){
        createText("Draw!", "BebasNeue.otf", {camera_.getPosition().x, camera_.getPosition().y - Assets::WINDOW_SIZE.y / 2 + 150}, 32);
        gameWindow->clear({0,255,255});
    }

    draw();
    gameWindow->display();
    while(!input->mouseReleased()){
        input->update(gameWindow);
    }
    input->quitGame();
    
}
void GameWorld::createText(const std::string& text, const std::string& font, const sf::Vector2f& position, int size, const sf::Color& color, sf::Text::Style style){
    textVector_.push_back(std::move(std::unique_ptr<sf::Text>{new sf::Text(text, Assets::LOAD_FONT(font), size)}));
    textVector_.back()->setOrigin({textVector_.back()->getLocalBounds().width/2, textVector_.back()->getLocalBounds().height/2});
    textVector_.back()->setPosition(position);
    textVector_.back()->setStyle(style);
    textVector_.back()->setColor(color);
}

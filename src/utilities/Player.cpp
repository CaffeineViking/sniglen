#include "Player.hpp"

Player::Player(sf::Color col) : color_{col}{
    weaponList_.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new Bazooka()}, 10));
    weaponList_.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new MiniBaz()}, 0));
    weaponList_.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new Nuke()}, 0));
}

Player::~Player(){
    for(Unit* unit : team_)
        delete unit;
}

Unit* Player::getRandomUnit(){
    if(team_.size() != 0 && teamAlive())
        return team_[Random::GENERATE_MAX(team_.size()-1)]; // Return random unit from team

    return nullptr;
}

bool Player::teamAlive(){
    short unsigned int deadUnits{0};
    for(unsigned i{0}; i < team_.size(); ++i){
        if(team_[i]->isDead())
            ++deadUnits;
    }
    if(deadUnits == team_.size())
        return false;
    return true;
}

bool Player::isTeamDead(){
    short unsigned int deadUnits{0};
    for(unsigned i{0}; i < team_.size(); ++i){
        if(team_[i]->isDead())
            ++deadUnits;
    }
    if(deadUnits == team_.size())
        return true;
    return false;
}

Unit* Player::getNextUnit(){
    if(team_.size() != 0 && teamAlive()){
        if(unitCounter_+1 >= (int)team_.size()){ // Make sure that the unit counter is in bounds
            unitCounter_ = -1; 
        }
        return team_[++unitCounter_]; // Return next unit
    }

    return nullptr;
}
void Player::selectWeapon(int weaponID){
    if(!weaponList_.empty()){
        if (weaponID > (int)weaponList_.size() - 1) // Make sure weapon selected is within bounds
            weaponID = 0; // Reset if selcected been to large */
        currentWeapon_ = weaponID; // Save the current weapon in the pointer variable
    }
}
void Player::insertUnit(Unit* unit){
    unit->setColor(color_);
    team_.push_back(unit);
}

std::unique_ptr<Weapon>& Player::getCurrentWeapon(){
    return weaponList_[currentWeapon_].first;
}

int Player::getCurrentWeaponAmmo() const {
    return weaponList_[currentWeapon_].second;
}
std::string Player::getCurrentWeaponString() const {
    if (currentWeapon_ == 0) {
        return "Bazooka";
    } else if (currentWeapon_ == 1) {
        return "MiniBaz";
    } else if (currentWeapon_ == 2) {
        return "Nuke";
    }

    return "Mystery Weapon";
}

void Player::increaseAmmo(int weaponID, unsigned ammo) {
    weaponList_[weaponID].second += ammo;
}

void Player::useCurrentWeapon() {
    --weaponList_[currentWeapon_].second;
}

void Player::removeUnits() {
    unsigned removed{0};
    unsigned iteratedOver{0};
    if(!team_.empty()){
        while(iteratedOver + removed < team_.size()){
            if(team_.at(iteratedOver)->isRemoved()){
                team_.at(iteratedOver) = nullptr;
                std::swap(team_.at(iteratedOver), (team_.at(team_.size()-(++removed))));
            }
            else
                ++iteratedOver;
        }

        team_.erase(team_.begin() + (team_.size()-removed), team_.end());
    }
}

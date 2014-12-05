#include "Player.hpp"

Player::Player(sf::Color col) : color_{col}{
    weaponList_.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new Bazooka()}, 25));
    weaponList_.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new MiniBaz()}, 5));
    weaponList_.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new Nuke()}, 2));
}

Player::~Player(){
    for(Unit* unit : team_)
        delete unit;
    team_.clear();
}

Unit* Player::getRandomUnit(){
    return team_[Random::GENERATE_MAX(team_.size()-1)]; // Return random unit from team
}

Unit* Player::getNextUnit(){
    if(unitCounter_+1 >= (int)team_.size()){ // Make sure that the unit counter is in bounds
        unitCounter_ = -1; 
    }
    return team_[++unitCounter_]; // Return next unit
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


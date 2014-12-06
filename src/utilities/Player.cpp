#include "Player.hpp"

Player::Player(sf::Color col) : color_{col}{
    weaponList_.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new Bazooka()}, 25));
    weaponList_.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new MiniBaz()}, 5));
    weaponList_.push_back(std::make_pair<std::unique_ptr<Weapon>, int>(std::unique_ptr<Weapon>{new Nuke()}, 2));
}

Player::~Player(){
    for(Unit* unit : team_)
        delete unit;
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

#include "Player.hpp"

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

Weapon* Player::getCurrentWeapon(){
    return weaponList_[currentWeapon_].first;
}


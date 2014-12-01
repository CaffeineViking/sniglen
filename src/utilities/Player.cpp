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
Weapon* Player::selectWeapon(int weaponID){
    if (weaponID > (int)weaponList_.size()-1) // Make sure weapon selected is within bounds
        weaponID = 1; // Increment as more weapons gets implemented
    currentWeapon_ = weaponID; // Save the current weapon in the pointer variable
    return weaponList_[weaponID].first; // Return weapon
}
void Player::insertUnit(Unit* unit){
    unit->setColor(color_);
    team_.push_back(unit);
}

int Player::getCurrentWeapon(){
    return currentWeapon_;
}


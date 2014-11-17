#include "Player.hpp"

Unit* Player::getRandomUnit(){
    return team_[Random::GENERATE_MAX(team_.size()-1)]; // Return random unit from team
}
Unit* Player::getNextUnit(){
    if(unitCounter_+1 >= team_.size()){ // Make sure that the unit counter is in bounds
        unitCounter_ = -1; 
    }
    return team_[++unitCounter_]; // Return next unit
}
Weapon* Player::selectWeapon(int weaponID){
    if (weaponID > weaponList_.size()-1) // Make sure weapon selected is within bounds
        weaponID = 1; // Increment as more weapons gets implemented
    return weaponList_[weaponID]; // Return weapon
}

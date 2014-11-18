#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
#include "Random.hpp"
#include "Weapon.hpp"
#include "../entities/Entity.hpp"

class Player{
    private:
        sf::Color color_;
        std::vector<std::pair<Weapon*, int>> weaponList_; // Vector of weapon and ammunition of each of them
        std::vector<Unit*> team_;
        int unitCounter_{-1};
    public:
        Player(sf::Color col) : color_{col}{}
        Player(){}
        Unit* getRandomUnit();
        Unit* getNextUnit();
        Weapon* selectWeapon(int weaponID);
        ~Player() = default;
};
#endif

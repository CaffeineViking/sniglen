#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <utility>
#include <memory>
#include <vector>
#include "Random.hpp"
#include "Weapon.hpp"
#include "../entities/Entity.hpp"

class Unit;
class Player{
    private:
        sf::Color color_;
        std::vector<std::pair<std::unique_ptr<Weapon>, int>> weaponList_; // Vector of weapon and ammunition of each of them
        std::vector<Unit*> team_;
        int unitCounter_{-1};
        int currentWeapon_{0};
        bool teamAlive();
    public:
        Player(sf::Color col);
        ~Player();
        sf::Color getColor(){return color_;};
        Unit* getRandomUnit();
        Unit* getNextUnit();
        const std::vector<Unit*>& getTeam(){return team_;};
        void insertUnit(Unit*);
        bool isTeamDead();
        void selectWeapon(int weaponID);
        std::unique_ptr<Weapon>& getCurrentWeapon();
        std::string getCurrentWeaponString() const;
        int getCurrentWeaponAmmo() const;
        void increaseAmmo(int, unsigned);
        void useCurrentWeapon();
        void removeUnits();
};
#endif

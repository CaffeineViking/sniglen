#ifndef CRATE_HPP
#define CRATE_HPP

#include "Entity.hpp"
#include "../utilities/Assets.hpp"
#include "../utilities/Weapon.hpp"
#include "../environment/Environment.hpp"

class Crate : public Entity {
public:
    Crate(const sf::Vector2f& pos)
        : Entity{Assets::LOAD_TEXTURE("crate.png"), pos, 0.0f, 1} {}
    void applyPhysics(bool, Environment&) override;
    bool isColliding(const Entity&);
};

class HealthCrate : public Crate {
public:
    float pickUp();
    HealthCrate(const sf::Vector2f& pos)
        : Crate{pos} {}
};

class WeaponCrate : public Crate {
public:
    std::pair<int, int> pickUp();
    WeaponCrate(const sf::Vector2f& pos)
        : Crate{pos} {}
};

#endif

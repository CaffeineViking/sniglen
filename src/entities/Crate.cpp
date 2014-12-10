#include "Crate.hpp"

#include "../utilities/Random.hpp"

void Crate::applyPhysics(bool colliding, Environment& environment) {
    // Temporary collision handling.
    if (!colliding) {
        Entity::applyPhysics(colliding, environment);
    } else {
        momentum_.y = 0.0f;
    }
}

bool Crate::isColliding(const Entity& entity) {
    return getSprite().getGlobalBounds().intersects(entity.getSprite().getGlobalBounds());
}

float HealthCrate::pickUp() {
    remove();
    return Random::GENERATE_MINMAX(1, 3) * 5.0f;
}

std::pair<int, int> WeaponCrate::pickUp() {
    remove();
    std::pair<int, int> weapon;
    weapon.first = Random::GENERATE_MINMAX(0, 2);
    weapon.second = Random::GENERATE_MINMAX(3, 8);
    return weapon;
}

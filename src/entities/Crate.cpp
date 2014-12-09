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

Weapon* WeaponCrate::pickUp() {
    remove();
    return nullptr;
}

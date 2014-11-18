#include "Environment.hpp"
#include "../utilities/Random.hpp"

void Environment::randomizeWind() {
    windForce_ = Random::GENERATE_MINMAX(-100, 100) / 100.0f;
}

float Environment::getWindForce() const {
    return windForce_;
}

float Environment::getGravity() const {
    return gravity_;
}

Terrain& Environment::getTerrain() {
    return terrain_;
}

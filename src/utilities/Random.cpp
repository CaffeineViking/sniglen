#include "Random.hpp"

unsigned Random::GENERATE() {
    return RNG();
}

int Random::GENERATE_MAX(int max) {
    return GENERATE() % max + 1;
}

int Random::GENERATE_MINMAX(int min, int max) {
    return (GENERATE() % (max - min + 1)) + min;
}

std::random_device Random::RNG;

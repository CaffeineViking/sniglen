#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "Terrain.hpp"

class Environment {
public:
    Environment() = default;
    Environment(float gravity, unsigned terrain_size) : gravity_{gravity}, terrain_{terrain_size} {}

    void randomizeWind();
    float getWindForce() const;
    float getGravity() const;
    const Terrain& getTerrain() const;

private:
    float windForce_{0.0f};
    const float gravity_{9.82f};
    Terrain terrain_{6144};
};

#endif

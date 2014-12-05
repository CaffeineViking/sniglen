#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
//class Terrain;
#include "Terrain.hpp"
class Environment {
public:
    Environment() = default;
    Environment(float gravity, unsigned terrain_size) : gravity_{gravity}, terrain_{terrain_size}, terrainSize_{terrain_size} {}

    void randomizeWind();
    float getWindForce() const;
    float getGravity() const;
    Terrain& getTerrain();
    unsigned getTerrainSize() const;

private:
    float windForce_{0.0f};
    const float gravity_{9.82f};
    Terrain terrain_{2560};
    unsigned terrainSize_{2560};
};

#endif

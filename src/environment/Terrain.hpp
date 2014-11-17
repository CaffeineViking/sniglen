#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "../entities/Entity.hpp"

// Provides a two dimensional, randomly generated terrain
// using Perlin Noise. Additionaly, collision between
// Terrain and Entity can be checked (via pixel collision).

class Terrain {
public:
    Terrain(unsigned);
    void draw(sf::RenderWindow&) const; // Draws the generated terrain sprite to the main window.
    bool isColliding(const Entity&) const; // Checks the generated Perlin Noise function if a
    // intersection between the curve function and the entity is happening.

private:
    sf::Sprite sprite_;
    sf::Texture texture_;
    sf::Image image_;
    std::vector<double> data_;
};

#endif

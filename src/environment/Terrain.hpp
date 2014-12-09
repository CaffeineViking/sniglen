#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "../entities/Entity.hpp"

// Provides a two dimensional, randomly generated terrain
// using Perlin Noise. Additionaly, collision between
// Terrain and Entity can be checked (via pixel collision).

class Entity;
class Terrain {
public:
    Terrain(unsigned);
    void destroy(const sf::CircleShape&); // Destroys part of the terrain.
    void destroy(sf::Vector2i, float); // Destroys part of the terrain.
    void draw(sf::RenderWindow&) const; // Draws the generated terrain sprite to the main window.
    bool isColliding(const Entity&) const; // Checks the generated Perlin Noise function if a
    std::pair<bool, bool> Terrain::goLeftRightCheckSlope(const sf::Vector2f slopePoint);
    // intersection between the curve function and the entity is happening.

private:
    void refresh(); // Updates the terrain texture.
    sf::Sprite sprite_;
    sf::Texture texture_;
    sf::Image image_;
};

#endif

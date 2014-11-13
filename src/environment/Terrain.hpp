#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "../entities/Entity.hpp"

class Terrain : public sf::Sprite {
public:
    Terrain(unsigned);
    void draw(sf::RenderWindow&) const;
    bool isColliding(const Entity&) const;

private:
    sf::Sprite sprite_;
    sf::Texture texture_;
    sf::Image image_;
    std::vector<double> data_;
};

#endif

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Terrain {
public:
    Terrain(unsigned size);
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite_;
    sf::Texture texture_;
    sf::Image image_;
    std::vector<double> data_;
};

#endif

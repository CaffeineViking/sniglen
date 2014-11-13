#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Terrain : public sf::Sprite {
public:
    Terrain(unsigned);
    void draw(sf::RenderWindow&) const;

private:
    sf::Sprite sprite_;
    sf::Texture texture_;
    sf::Image image_;
    std::vector<double> data_;
};

#endif

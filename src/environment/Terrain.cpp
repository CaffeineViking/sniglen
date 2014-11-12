#include "Terrain.hpp"

#include "../utilities/Random.hpp"
#include "../perlinnoise/PerlinNoise.hpp"
#include <iostream>

Terrain::Terrain(unsigned size) {
    image_.create(size, 540, {0, 0, 0, 0});
    const PerlinNoise perlin{Random::GENERATE()};

    const double frequency{4.0f};
    const double frequency_x{image_.getSize().x / frequency};
    const double frequency_y{image_.getSize().y / frequency};

    sf::Image terrain_texture;
    terrain_texture.loadFromFile("share/terrain.png");

    for (size_t x{0}; x < image_.getSize().x; ++x) {
        const double noise{(perlin.octaveNoise(x / frequency_x, 3) + 1.0) / 2.0};
        for (size_t y{noise * image_.getSize().y}; y < image_.getSize().y; ++y) {
            size_t x_mod{x % terrain_texture.getSize().x};
            size_t y_mod{y % terrain_texture.getSize().y};
            sf::Color pix{terrain_texture.getPixel(x_mod, y_mod).r,
                          terrain_texture.getPixel(x_mod, y_mod).g,
                          terrain_texture.getPixel(x_mod, y_mod).b};

            if (y < noise * image_.getSize().y + 10) {
                image_.setPixel(x, y, {96, 83, 66});
            } else {
                image_.setPixel(x, y, pix);
            }
        }
    }

    texture_.loadFromImage(image_);
    sprite_.setTexture(texture_);
    sprite_.move(0, 720 - image_.getSize().y);
}

const sf::Sprite& Terrain::getSprite() const {
    return sprite_;
}

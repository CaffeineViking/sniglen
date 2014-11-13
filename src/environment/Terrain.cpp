#include "Terrain.hpp"

#include "../utilities/Random.hpp"
#include "../perlinnoise/PerlinNoise.hpp"
#include <iostream>

Terrain::Terrain(unsigned size) {
    image_.create(size, 540, {0, 0, 0, 0});
    const PerlinNoise perlin{Random::GENERATE()};

    const double frequency{(size / 1024) * 2.5f};
    const double frequencyX{image_.getSize().x / frequency};

    sf::Image terrainTexture;
    terrainTexture.loadFromFile("share/terrain.png");

    for (size_t x{0}; x < image_.getSize().x; ++x) {
        const double noise{(perlin.octaveNoise(x / frequencyX, 3) + 1.0) / 2.0};
        data_.push_back(noise * image_.getSize().y);

        for (size_t y{noise * image_.getSize().y}; y < image_.getSize().y; ++y) {
            size_t xMod{x % terrainTexture.getSize().x};
            size_t yMod{y % terrainTexture.getSize().y};
            sf::Color pix{terrainTexture.getPixel(xMod, yMod).r,
                terrainTexture.getPixel(xMod, yMod).g,
                terrainTexture.getPixel(xMod, yMod).b};

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

void Terrain::draw(sf::RenderWindow& window) const {
    window.draw(sprite_);
}

bool Terrain::isColliding(const Entity& entity) const {
    if (entity.getPos().x < 0 || entity.getPos().x > image_.getSize().x) {
        return false;
    } else {
        return entity.getPos().y > (sprite_.getPosition().y + data_[entity.getPos().x]);
    }
}

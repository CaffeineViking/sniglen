#include "Terrain.hpp"

#include "../utilities/Random.hpp"
#include "../perlinnoise/PerlinNoise.hpp"
#include <iostream>

Terrain::Terrain(unsigned size) {
    // Allocate a image with the desired size of the terrain.
    image_.create(size, 540, {0, 0, 0, 0});
    const PerlinNoise perlin{Random::GENERATE()};

    // These change the frequency of the "bumps" on the terrrain.
    const double frequency{(size / 1024) * 2.5f};
    const double frequencyX{image_.getSize().x / frequency};

    // A texture will overlay the generated terrain, load this.
    sf::Image terrainTexture;
    terrainTexture.loadFromFile("share/terrain.png");

    // For every pixel in width, generate a noise "height".
    for (size_t x{0}; x < image_.getSize().x; ++x) {
        const double noise{(perlin.octaveNoise(x / frequencyX, 3) + 1.0) / 2.0};
        data_.push_back(noise * image_.getSize().y);

        // Also, copy pixels from the terrain overlay to every area below the generated height.
        for (size_t y{noise * image_.getSize().y}; y < image_.getSize().y; ++y) {
            size_t xMod{x % terrainTexture.getSize().x};
            size_t yMod{y % terrainTexture.getSize().y};
            sf::Color pix{terrainTexture.getPixel(xMod, yMod).r,
                terrainTexture.getPixel(xMod, yMod).g,
                terrainTexture.getPixel(xMod, yMod).b};

            // Check if we need to generate the beautiful terrain outline.
            if (y < noise * image_.getSize().y + 10) {
                image_.setPixel(x, y, {96, 83, 66});
            } else {
                image_.setPixel(x, y, pix);
            }
        }
    }

    refresh(); // Write terrain to texture.
    sprite_.move(0, 720 - image_.getSize().y);
}

void Terrain::refresh() {
    texture_.loadFromImage(image_);
    sprite_.setTexture(texture_);
}

void Terrain::destroy(int x, int y, float radius) {
    refresh();
}

void Terrain::draw(sf::RenderWindow& window) const {
    window.draw(sprite_);
}

bool Terrain::isColliding(const Entity& entity) const {
    // This initial check here saves us the trouble from out of bounds errors.
    if (entity.getPos().x < 0 || entity.getPos().x > image_.getSize().x) {
        return false;
    } else {
        // See if part of the entity is below the generated terrain height.
        return entity.getPos().y > (sprite_.getPosition().y + data_[entity.getPos().x]);
    }
}

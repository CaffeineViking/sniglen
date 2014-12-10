#include "Terrain.hpp"

#include "../utilities/Assets.hpp"
#include "../utilities/Random.hpp"
#include "../perlinnoise/PerlinNoise.hpp"
#include <cmath>
#include <utility>

Terrain::Terrain(unsigned size) {
    // Allocate a image with the desired size of the terrain.
    image_.create(size, 540, {0, 0, 0, 0});
    const PerlinNoise perlin{Random::GENERATE()};

    // These change the frequency of the "bumps" on the terrrain.
    const double frequency{(size / 1024) * 2.5f};
    const double frequencyX{image_.getSize().x / frequency};

    // A texture will overlay the generated terrain, load this.
    sf::Image terrainTexture{Assets::LOAD_TEXTURE("terrain.png").copyToImage()};

    // For every pixel in width, generate a noise "height".
    for (size_t x{0}; x < image_.getSize().x; ++x) {
        const double noise{(perlin.octaveNoise(x / frequencyX, 3) + 1.0) / 2.0};

        // Also, copy pixels from the terrain overlay to every area below the generated height.
        for (size_t y = noise * image_.getSize().y; y < image_.getSize().y; ++y) {
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

std::pair<bool, bool> Terrain::goLeftRightCheckSlope(const sf::Vector2f slopePoint) {
    std::pair<bool, bool> tmp = std::make_pair(false, false); 
    for(int i {0}; i <= 2; i++) {
        if(image_.getPixel(slopePoint.x-2, slopePoint.y+50+i).a == 0) {
            tmp.first = true;
            std::cerr << "left dont go" << std::endl;
            break;
        }
    }

    for(int i {0}; i<= 2; i++) {
        if(image_.getPixel(slopePoint.x+2, slopePoint.y+50+i).a == 0) {
            tmp.second = true;
            std::cerr << "right side dont go pliiizzzzz" << std::endl;
            break;
        }
    }
    return tmp;
}

void Terrain::refresh() {
    texture_.loadFromImage(image_);
    sprite_.setTexture(texture_);
}

void Terrain::destroy(const sf::CircleShape& explosion) {
    destroy(static_cast<sf::Vector2i>(explosion.getPosition()), explosion.getRadius());
}

void Terrain::destroy(sf::Vector2i position, float radius) {
    // These variables will be used to check if the bounds of the terrain have been crossed.
    int terrainMaxY = sprite_.getPosition().y + sprite_.getTexture()->getSize().y;
    int terrainMaxX = sprite_.getPosition().x + sprite_.getTexture()->getSize().x;

    for (int y = position.y - radius; y <= position.y + radius; ++y) {
        if (y < sprite_.getPosition().y || y >= terrainMaxY) continue;
        for (int x = position.x - radius; x <= position.x + radius; ++x) {
            if (x < sprite_.getPosition().x || x >= terrainMaxX) continue;
            // Determine distance between origin and current checked pixel.
            unsigned distance = std::sqrt(std::pow(x - position.x, 2) + std::pow(y - position.y, 2));

            // If the distance is smaller than the target radius, clear that pixel (we are in the circle).
            if (distance <= radius) {
                image_.setPixel(x - sprite_.getPosition().x, y - sprite_.getPosition().y, {0, 0, 0, 0});
            }
        }
    }

    // The image has been updated, the texture and sprite need to be notified.
    refresh();
}

void Terrain::draw(sf::RenderWindow& window) const {
    window.draw(sprite_);
}

bool Terrain::isColliding(const Entity& entity) const {
    const sf::Image& entityImage{entity.getSpriteData()}; // Could be bottleneck here if there is one. Need this in Entity instead.

    // The start coordiantes to check pixels. These use the entities sprite size, no need to check the entire terrain.
    int startX = (entity.getPos().x - entityImage.getSize().x / 2) - sprite_.getPosition().x;
    int startY = (entity.getPos().y - entityImage.getSize().y / 2) - sprite_.getPosition().y;

    // int startX = entity.getPos().x - 5  - sprite_.getPosition().x;
    // int startY = entity.getPos().y + ((entityImage.getSize().y / 2) - 10 ) - sprite_.getPosition().y;

    // The end coordinates to check for a pixel collision.
    // int endX = startX + 10;
    // int endY = startY + 10;
    int endX = startX + entity.getSprite().getTexture()->getSize().x;
    int endY = startY + entity.getSprite().getTexture()->getSize().y;

    for (int y{startY}; y < endY; ++y) {
        // Make sure we are within bounds.
        if (y < 0 || y >= static_cast<int>(sprite_.getTexture()->getSize().y)) continue;
        for (int x{startX}; x < endX; ++x) {
            if (x < 0 || x >= static_cast<int>(sprite_.getTexture()->getSize().x)) continue;
            // If both (terrain and entity) pixel colors are NOT transparent, we have a collision.
            if (image_.getPixel(x, y).a != 0 && entityImage.getPixel(x - startX, y - startY).a != 0) return true;
        }
    }

    // Otherwise no collision.
    return false;
}

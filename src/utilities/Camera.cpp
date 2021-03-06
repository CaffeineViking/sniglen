#include "Camera.hpp"

Camera::Camera(const sf::RenderWindow& window)
    : view_{window.getDefaultView()} {}

void Camera::toggleZoom(const Environment& environment) {
    zoomed_ = !zoomed_;

    if (zoomed_) {
        view_.zoom(environment.getTerrainSize() / 1280.0f);
    } else {
        view_.zoom(1280.0f / environment.getTerrainSize());
    }
}

void Camera::update(const Entity* followTarget, const Environment& environment, float yBounds) {
    float newCameraX{getPosition().x};
    float newCameraY{getPosition().y};
    if (zoomed_) {
        newCameraX = environment.getTerrainSize() / 2.0f;
        newCameraY = 0.0f;
    } else {
        if (followTarget->getPos().x - view_.getSize().x / 4.0f < 0.0f) {
            // Keep the camera still when followTarget has reached the left end of the terrain.
            newCameraX = view_.getSize().x / 2.0f;
        } else if (followTarget->getPos().x + view_.getSize().x / 4.0f > environment.getTerrainSize()) {
            // Keep the camera still when followTarget has reached the right end of the terrain.
            newCameraX = environment.getTerrainSize() - view_.getSize().x/2;
        } else if (followTarget->getPos().x > getPosition().x + view_.getSize().x / 4.0f) {
            // The camera can move right when followTarget is within the left bounds.
            newCameraX = followTarget->getPos().x - view_.getSize().x/4;
        } else if (followTarget->getPos().x < getPosition().x - view_.getSize().x / 4.0f) {
            // The camera can move left when followTarget is within the left bounds.
            newCameraX = followTarget->getPos().x + view_.getSize().x / 4.0f;
        }

        if (followTarget->getPos().y > getPosition().y + view_.getSize().y / 4.0f) {
            newCameraY = followTarget->getPos().y - view_.getSize().y / 4.0f;
        } else if (followTarget->getPos().y < getPosition().y - view_.getSize().y / 4.0f) {
            newCameraY = followTarget->getPos().y + view_.getSize().y / 4.0f;
        }
    }

    if (newCameraY > yBounds) {
        newCameraY = yBounds;
    }

    // Update the camera position with the information calculated above.
    view_.setCenter(newCameraX, newCameraY);
}

const sf::Vector2f& Camera::getPosition() const {
    return view_.getCenter();
}

void Camera::draw(sf::RenderWindow& window) const {
    window.setView(view_);
}

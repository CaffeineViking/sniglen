#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../entities/Entity.hpp"
#include "../environment/Environment.hpp"

class Camera {
public:
    Camera(const sf::RenderWindow&);

    void toggleZoom(const Environment&);
    void update(const Entity*, const Environment&, float);
    const sf::Vector2f& getPosition() const;
    void draw(sf::RenderWindow&) const;

private:
    bool zoomed_{false};
    sf::View view_;
};

#endif

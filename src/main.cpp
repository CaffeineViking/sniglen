#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "entities/Entity.hpp"

int main() {
    sf::RenderWindow window{sf::VideoMode{1280, 720}, "TDDI02 - Made in Vim", sf::Style::Close};
    window.setFramerateLimit(60);
    GameWorld game{window};

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        game.update();
        window.clear();
        game.draw();
        // game.drawCamera();
        // game.drawMinimap();
        window.display();
    }

    return 0;
}

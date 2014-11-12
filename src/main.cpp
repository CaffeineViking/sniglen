#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "entities/Entity.hpp"

int main() {
    sf::RenderWindow window{sf::VideoMode{1280, 720}, "TDDI02", sf::Style::Close};
    window.setFramerateLimit(60);
    GameWorld game{window};

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                game.keyPressed(event.key.code);
            } else if (event.type == sf::Event::KeyReleased) {
                game.keyReleased(event.key.code);
            } else if (event.type == sf::Event::MouseButtonPressed) {
                game.mousePressed(event.mouseButton.button);
            } else if (event.type == sf::Event::MouseButtonReleased) {
                game.mouseReleased(event.mouseButton.button);
            }

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
        window.display();
    }

    return 0;
}

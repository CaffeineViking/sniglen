#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "entities/Entity.hpp"
#include "utilities/InputHandler.hpp"

enum class gameState{menu = 0, game, pause};

int main() {
    sf::RenderWindow window{sf::VideoMode{1280, 720}, "TDDI02 - Made in Vim", sf::Style::Close};
    window.setFramerateLimit(60);
    InputHandler input;
    GameWorld game{window, input};
    gameState state = gameState::menu;

    while (window.isOpen()){
        sf::Event event;
        input.update(&window);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (input.isKeyPressed(sf::Keyboard::Key::Escape)) {
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

#include <SFML/Graphics.hpp>
#include "GameWorld.hpp"
#include "MenuScreen.hpp"
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
        if(input.isKeyReleased(sf::Keyboard::Key::Num1)){
            if(state == gameState::menu)
                state = gameState::game;
            else
                state = gameState::menu;
        }

        if(state == gameState::game){
            game.update();
            std::cout << "game is updating yes" << std::endl;
        }
        else if(state == gameState::menu){
            std::cout << "meny is updating yes" << std::endl;
        }
        window.clear();
        if(state == gameState::game){
            game.draw();
            std::cout << "game is drawing yes" << std::endl;
        }
        else if(state == gameState::menu){
            std::cout << "meny is drawing yes" << std::endl;
        }
        // game.drawCamera();
        // game.drawMinimap();

        window.display();
    }

    return 0;
}

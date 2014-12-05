#include <SFML/Graphics.hpp>
#include "utilities/Assets.hpp"
#include "GameWorld.hpp"
#include "MenuScreen.hpp"
#include "entities/Entity.hpp"
#include "utilities/InputHandler.hpp"
#include <iostream>

enum class gameState{menu = 0, game, pause};

int main() {
    sf::RenderWindow window{sf::VideoMode(Assets::WINDOW_SIZE.x, Assets::WINDOW_SIZE.y), "Sniglen: the Game: the Movie: Reloaded: Limited Limited Edition! - Made by ~xX|Azzazzin98|Xx~, .-:Sup3r1337k1ll4|c4p4c0p:-. and rumpnisse", sf::Style::Close};
    window.setFramerateLimit(60);
    Assets::LOAD_FONT("BebasNeue.otf");
    InputHandler input;
    GameWorld game{window, input};
    MenuScreen menu{window, input};
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
        if(input.isKeyReleased(sf::Keyboard::Key::Delete)){
            if(state == gameState::menu)
                state = gameState::game;
            else
                state = gameState::menu;
        }

        if(state == gameState::game){
            game.update();
        }
        else if(state == gameState::menu){
            window.setView(window.getDefaultView());
            menu.update();
            if(menu.getGameStart()){
                state = gameState::game;
                game.initiate(menu.getPlayerAmount(), menu.getTeamSize());
            }
        }

        const sf::Color CLEAR_COLOR{0x30, 0x30, 0x30};
        window.clear(CLEAR_COLOR); // Jättefint.

        if(state == gameState::game){
            game.draw();
        }
        else if(state == gameState::menu){
            menu.draw();
        }

        window.display();
    }

    return 0;
}

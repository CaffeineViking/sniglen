#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Entity/Entity.hpp"

using namespace std;

sf::Texture loadTexture(string);
int main() {
    
    sf::RenderWindow window{sf::VideoMode{1280, 720}, "GeglQuest", sf::Style::Close};
    
    GameWorld game{window};
    
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event == sf::Event::KeyPressed)
                game.keyPressed(event.key.code);
                
            if (event == sf::Event::KeyReleased)
                game.keyReleased(event.key.code);
                
            if (event == sf::Event::MouseButtonPressed)
                game.mousePressed(event.mouse.button);
                
            if (event == sf::Event::MouseButtonReleased)
                game.mouseReleased(event.mouse.button);
                
            /*if (event == sf::Event::JoystickButtonPressed)
                
            if (event == sf::Event::JoystickButtonReleased)*/
            
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        //gegl.update();
        window.clear();
        game.update();
        window.display();
    }
    return 0;
}

sf::Texture loadTexture(const string& fileName){
    sf::Texture temp;
    temp.loadFromFile(fileName);
    return temp;
}

#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Entity/Entity.hpp"

using namespace std;

sf::Texture loadTexture(string);
int main() {
    std::cout << "Hello, world!" << std::endl;
    //Unit gegl(loadTexture("share/Gegl.jpg"), sf::Vector2f{50,50}, 5, 500);
    sf::RenderWindow window{sf::VideoMode{1280, 720}, "GeglQuest", sf::Style::Close};
    while(window.isOpen()){
        sf::Event event;
        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        //gegl.update();
        window.clear();
        window.display();
    }
    return 0;
}

sf::Texture loadTexture(const string& fileName){
    sf::Texture temp;
    temp.loadFromFile(fileName);
    return temp;
}

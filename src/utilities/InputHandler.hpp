#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <set>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>


class InputHandler{
    private:
        std::set<sf::Keyboard::Key> pressedKeys_;
        std::set<sf::Keyboard::Key> releasedKeys_;
        bool mouseClicked_;
        bool mouseReleased_;
        sf::Vector2i mousePos_;
        void keyboardUpdate();
        void mouseUpdate(sf::RenderWindow* window);
    public:
        InputHandler() = default;
        const std::set<sf::Keyboard::Key>& getPressedKeys(){return pressedKeys_;};
        const std::set<sf::Keyboard::Key>& getReleasedKeys(){return releasedKeys_;};
        bool isKeyPressed(sf::Keyboard::Key key);
        bool mouseClicked(){return mouseClicked_;};
        bool mouseReleased(){return mouseReleased_;};
        const sf::Vector2i& mousePosition(){return mousePos_;};
        void update(){keyboardUpdate();};
        void update(sf::RenderWindow* window){keyboardUpdate(); mouseUpdate(window);};
};
#endif

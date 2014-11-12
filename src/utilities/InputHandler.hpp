#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <vector>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

class InputHandler{
    private:
        std::vector<sf::Keyboard::Key> pressedKeys_;
        std::vector<sf::Keyboard::Key> releasedKeys_;
        bool mouseClicked_;
        bool mouseReleased_;
        sf::Vector2f mousePos_;
        void keyboardUpdate();
        void mouseUpdate();
    public:
        const std::vector<sf::Keyboard::Key>& getPressedKeys(){return pressedKeys_;};
        const std::vector<sf::Keyboard::Key>& getReleasedKeys(){return releasedKeys_;};
        bool mouseClicked(){return mouseClicked_;};
        bool mouseReleased(){return mouseReleased_;};
        const sf::Vector2f& mousePosition(){return mousePos_;};
        void update(){keyboardUpdate(); mouseUpdate();};
};
#endif

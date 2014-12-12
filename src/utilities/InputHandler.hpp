#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <set>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>


class InputHandler{
    private:
        std::set<sf::Keyboard::Key> pressedKeys_;
        std::set<sf::Keyboard::Key> releasedKeys_;
        bool mouseClicked_ = false;
        bool mouseReleased_ = false;
        sf::Vector2i mousePos_;
        void keyboardUpdate();
        void mouseUpdate(sf::RenderWindow* window);
    public:
        InputHandler() = default;
        const std::set<sf::Keyboard::Key>& getPressedKeys() const {return pressedKeys_;};
        const std::set<sf::Keyboard::Key>& getReleasedKeys() const {return releasedKeys_;};
        bool isKeyPressed(sf::Keyboard::Key key) const;
        bool isKeyReleased(sf::Keyboard::Key key) const;
        bool mouseClicked() const {return mouseClicked_;};
        bool mouseReleased() const {return mouseReleased_;};
        const sf::Vector2i& mousePosition() const {return mousePos_;};
        void update(){keyboardUpdate();};
        void update(sf::RenderWindow* window){keyboardUpdate(); mouseUpdate(window);};
        void quitGame(){pressedKeys_.insert(sf::Keyboard::Key::Delete);};
};
#endif

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player{
    protected:
        sf::Color color_;
    public:
        Player(sf::Color col) : color_{col}{}
        Player(){}
        ~Player() = default;
};
#endif

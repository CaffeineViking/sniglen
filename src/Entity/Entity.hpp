#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <SFML/Graphics.hpp>
//#include "Player.h"
//#include "Weapons.h"
#include <iostream>
#include <vector>

class Entity{
    protected:
        sf::Texture texture_;
        sf::Sprite sprite_;
        sf::Vector2f position_;
        sf::Vector2f momentum_{0,0};
        sf::Vector2f maxMomentum_{10,10};
        const int mass_;
        const float gravity_{9.82};
        const float speed_;

        Entity(sf::Texture tex, sf::Vector2f pos, float spd, int mass):
            texture_{tex}, position_{pos}, speed_{spd}, mass_{mass}{ 
            sprite_.setTexture(texture_);
            sprite_.setPosition(pos);
        }

        virtual void getMovement(){}
        virtual void move(){}
        virtual void applyPhysics(){}
    public:
        sf::Sprite getSprite(){return sprite_;};
        sf::Vector2f getPos(){return position_;};
        virtual ~Entity() = default;
        virtual void update(){getMovement(); applyPhysics(); move();};
};

class Unit: public Entity{
    private:
        void getMovement();
        void applyPhysics() override;
        void move() override;
    public:

        Unit(sf::Texture tex, sf::Vector2f pos, float spd, int mass): 
            Entity(tex, pos, spd, mass){ sprite_.setPosition(position_);}
        //Unit(sf::Texture tex, sf::Vector2f pos, float spd, int mass, Player* player = nullptr): 
            //Entity(tex, pos, spd, mass), owner_{player}{ sprite_.setPosition(position_);}
        void update(){getMovement(); applyPhysics(); move();};
};

class Projectile: public Entity{
    private:
        //Weapon* type_;
        float angle_;
    public:
        bool deleted_ = false;
        //Projectile(sf::Texture tex, sf::Vector2f pos, float spd, int mass, sf::Vector2f inMom, float angle, Weapon* weapon):
            //Entity(tex, {pos.x, pos.y-1}, spd, mass), type_{weapon}{
               // if(inMom.x > 8)
                    //inMom.x = 8;
                //else if(inMom.x < -8)
                    //inMom.x = -8;
                //if(inMom.y > 8)
                    //inMom.y = 8;
                //else if(inMom.y < -40)
                    //inMom.y = -40;

                //momentum_ = {inMom.x, inMom.y};
                //sprite_.setPosition(position_);
            //}
        sf::CircleShape explode();
        void update();
        void applyPhysics() override;
        void move();

};

#endif
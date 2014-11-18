#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <SFML/Graphics.hpp>
#include "../utilities/Player.hpp"
#include "../utilities/Weapon.hpp"
#include "../utilities/InputHandler.hpp"
#include <iostream>
#include <vector>

class Player;
class Entity{
    protected:
        sf::Texture texture_;
        sf::Sprite sprite_;
        sf::Vector2f position_;
        sf::Vector2f momentum_{0,0};
        sf::Vector2f maxMomentum_{10,10};
        const int mass_;
        const float gravity_{9.82}; // Should be removed when Environment is implemented
        const float speed_;
        Entity(sf::Texture tex, sf::Vector2f pos, float spd, int mass):
            texture_{tex}, position_{pos}, mass_{mass}, speed_{spd}{
                sprite_.setTexture(texture_);
                sprite_.setPosition(pos);
            }
        bool lookLeft_{true};
        virtual void getMovement(const InputHandler&); // Reads input and sets what movements should be done
        virtual void applyPhysics(); // Applies friction and gravity to the movements that should be done
        virtual void move(); // Applies movement to the entity
    public:
        const sf::Sprite& getSprite() const {return sprite_;};
        const sf::Vector2f& getPos() const {return position_;};
        bool doUnitLookLeft(){return lookLeft_;};
        virtual ~Entity() = default;
        virtual void update(const InputHandler& input){getMovement(input); applyPhysics(); move();};
        virtual void collide();
        virtual void draw(sf::RenderWindow&); // Standardise draw functions
};

class Unit: public Entity{
    private:
        enum class unitState{idle=0, walking, falling, shooting};
        unitState state_; // Used to tell what the unit is currently doing
        Player* owner_;  
        int shootPower_{0}; // Release power of shots
        void getMovement(const InputHandler&) override;
        void applyPhysics() override;
        void move() override;

    public:
        Unit(sf::Texture tex, sf::Vector2f pos, float spd, int mass, Player* player = nullptr):
            Entity(tex, pos, spd, mass), owner_{player}{ sprite_.setPosition(position_);}
        void update(const InputHandler& input){getMovement(input); applyPhysics(); move();};
        void collide();
        bool isShooting(){return state_ == unitState::shooting;};
        int getShootPower(){return shootPower_;};
        ~Unit() = default;
};

class Projectile: public Entity{
    private:
        Weapon* type_; // Variable to keep track of what kind of weapon it is
        float angle_;
        void getMovement(const InputHandler&);
        void applyPhysics() override;
        void move();
    public:
        bool deleted_ = false;
        Projectile(sf::Texture tex, sf::Vector2f pos, float spd, int mass, sf::Vector2f inMom, float angle, Weapon* weapon):
            Entity(tex, {pos.x, pos.y-1}, spd, mass), type_{weapon}{
                if(inMom.x > 8)
                    inMom.x = 8;
                else if(inMom.x < -8)
                    inMom.x = -8;
                if(inMom.y > 8)
                    inMom.y = 8;
                else if(inMom.y < -40)
                    inMom.y = -40;
                momentum_ = {inMom.x, inMom.y};
                sprite_.setPosition(position_);
            }
        sf::CircleShape explode();
        void update(const InputHandler& input){getMovement(input); applyPhysics(); move();};

        ~Projectile() = default;
};

#endif

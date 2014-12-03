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
        Entity(const sf::Texture& tex, sf::Vector2f pos, float spd, int mass):
            texture_{tex}, position_{pos}, mass_{mass}, speed_{spd}{
                sprite_.setTexture(texture_);
                sprite_.setPosition(pos);
                sprite_.setOrigin({(float)texture_.getSize().x/2, (float)texture_.getSize().y/2});
            }
        bool lookLeft_{true};
        virtual void getMovement(const InputHandler&); // Reads input and sets what movements should be done
        virtual void applyPhysics(bool); // Applies friction and gravity to the movements that should be done
        virtual void move(); // Applies movement to the entity
    public:
        const sf::Sprite& getSprite() const {return sprite_;};
        const sf::Vector2f& getPos() const {return position_;};
        void setTexture(const sf::Texture& texture){sprite_.setTexture(texture);};
        bool doUnitLookLeft(){return lookLeft_;};
        virtual ~Entity() = default;
        virtual void update(const InputHandler& input, bool colliding){getMovement(input); applyPhysics(colliding); move();};
        virtual void collide();
        virtual void draw(sf::RenderWindow&); // Standardise draw functions
};

class Unit: public Entity{
    private:
        enum class unitState{idle=0, walking, falling, shooting};
        unitState state_; // Used to tell what the unit is currently doing
        Player* owner_;
        float aimAngle_ = 90;
        sf::Sprite crosshair_;
        int shootPower_{0}; // Release power of shots
        bool shoot_ = false;
        void getMovement(const InputHandler&) override;
        void getInput(const InputHandler&);
        void applyPhysics(bool) override;
        void move() override;
        void updateCrosshair();

    public:
        Unit(const sf::Texture& tex, const sf::Texture& crosshair, sf::Vector2f pos, float spd, int mass, Player* player = nullptr):
            Entity(tex, pos, spd, mass), owner_{player}, crosshair_(crosshair){ 
                sprite_.setPosition(position_);
                crosshair_.setPosition(sprite_.getOrigin());
                crosshair_.setOrigin({(float)crosshair_.getTexture()->getSize().x/2, (float)crosshair_.getTexture()->getSize().y/2});
                //crosshair_.setOrigin({(float)crosshair_.getTexture().getSize().x/2, (float)crosshair_.getTexture().getSize().y/2});
            }
        void update(const InputHandler& input, bool colliding) override {getInput(input); getMovement(input); updateCrosshair(); applyPhysics(colliding); move();};
        void collide();
        void checkExplosion(const sf::CircleShape&);
        bool inControl(){return (state_ != unitState::falling);};
        float getShootAngle(){return aimAngle_;};
        sf::Vector2f getShootMomentum(sf::RenderWindow&);
        sf::Vector2f getPosition() const {return sprite_.getPosition();}; // Kanske måste tas bort då vi redan har getPos sen förut!?
        void setColor(sf::Color color){sprite_.setColor(color);}
        bool isShooting(){return shoot_;};
        bool isDead(){return false;};
        void draw(sf::RenderWindow&) override;
        ~Unit() = default;
};

class Projectile: public Entity{
    private:
        float wind_;
        Weapon* type_; // Variable to keep track of what kind of weapon it is
        float angle_;
        bool removed_{false};
        void getMovement(const InputHandler&);
        void applyPhysics(bool) override;
        void move();
    public:
        bool deleted_ = false;
        bool isRemoved() const { return removed_; }
        Projectile(const sf::Texture& tex, const sf::Vector2f& pos, float spd, int mass, const sf::Vector2f& inMom, float wind, float angle, Weapon* weapon = nullptr ):
            Entity(tex, {pos.x, pos.y-1}, spd, mass), wind_{wind}, type_{weapon}, angle_{angle}{
                momentum_ = inMom;
                sprite_.setPosition(position_);
                if(angle == angle)
                    angle = angle;
            }
        sf::CircleShape explode();

        ~Projectile() = default;
};

#endif

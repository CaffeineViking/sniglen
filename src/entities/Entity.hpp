#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <SFML/Graphics.hpp>
#include "../utilities/Player.hpp"
#include "../utilities/Weapon.hpp"
#include "../environment/Terrain.hpp"
//#include "../environment/Environment.hpp"
#include "../utilities/InputHandler.hpp"
#include "../utilities/Assets.hpp"
#include <iostream>
#include <memory>
#include <vector>

//class Terrain;
class Environment;
class Player;
class Entity{
    protected:
        bool removed_{false};
        sf::Texture texture_;
        sf::Sprite sprite_;
        sf::Image sprite_data_;
        sf::Vector2f position_;
        sf::Vector2f momentum_{0,0};
        sf::Vector2f maxMomentum_{10,10};
        const int mass_;
        const float gravity_{9.82}; // Should be removed when Environment is implemented
        const float speed_;
        Entity(const sf::Texture& tex, sf::Vector2f pos, float spd, int mass):
            texture_{tex}, position_{pos}, mass_{mass}, speed_{spd}{
                setTexture(texture_);
                sprite_.setOrigin({(float)texture_.getSize().x/2, (float)texture_.getSize().y/2});
                sprite_.setPosition(pos);
            }
        bool lookLeft_{false};
        virtual void getMovement(const InputHandler&); // Reads input and sets what movements should be done
        virtual void applyPhysics(bool, Environment&); // Applies friction and gravity to the movements that should be done
        virtual void move(); // Applies movement to the entity
    public:
        void remove() { removed_ = true; }
        bool isRemoved() const { return removed_; }
        const sf::Sprite& getSprite() const {return sprite_;};
        const sf::Image& getSpriteData() const {return sprite_data_;};
        const sf::Vector2f& getPos() const {return sprite_.getPosition();};
        void setTexture(const sf::Texture& texture){sprite_.setTexture(texture); sprite_data_ = texture.copyToImage();};
        bool doUnitLookLeft(){return lookLeft_;};
        virtual ~Entity() = default;
        virtual void update(const InputHandler& input, bool colliding, Environment& environment){getMovement(input); applyPhysics(colliding, environment); move();};
        virtual void collide();
        virtual void draw(sf::RenderWindow&); // Standardise draw functions
};

class Unit: public Entity{
    private:
        float health_{10.0f};
        enum class unitState{idle=0, walking, falling, shooting};
        unitState state_ = unitState::falling; // Used to tell what the unit is currently doing
        Player* owner_;
        float aimAngle_ = 0;
        sf::Sprite crosshair_;
        sf::Text healthText_;
        int shootPower_{0}; // Release power of shots
        bool shoot_ = false;
        void getMovement(const InputHandler&) override;
        void getInput(const InputHandler&);
        void applyPhysics(bool, Environment&) override;
        sf::Vector2f findCollisionVector(const sf::Vector2f&, const sf::Vector2f&, Environment&);
        void move() override;
        void updateCrosshair();
        void updateHealthText();

    public:
        Unit(const sf::Texture& tex, const sf::Texture& crosshair, sf::Vector2f pos, float spd, int mass, Player* player = nullptr):
            Entity(tex, pos, spd, mass), owner_{player}, crosshair_(crosshair), healthText_(std::to_string(health_), Assets::LOAD_FONT("BebasNeue.otf")){
                sprite_.setPosition(position_);
                crosshair_.setOrigin({(float)crosshair_.getTexture()->getSize().x/2, (float)crosshair_.getTexture()->getSize().y/2});
                crosshair_.setPosition(sprite_.getOrigin());
                healthText_.setOrigin({healthText_.getLocalBounds().width/2, healthText_.getLocalBounds().height/2});
                healthText_.setPosition({sprite_.getPosition().x, sprite_.getPosition().y - 50});
            }

        const sf::Vector2f& getCrosshairPosition() const { return crosshair_.getPosition(); }
        void enableCrosshair() { crosshair_.setColor({crosshair_.getColor().r, crosshair_.getColor().g, crosshair_.getColor().b, 255}); }
        void disableCrosshair() { crosshair_.setColor({crosshair_.getColor().r, crosshair_.getColor().g, crosshair_.getColor().b, 0}); }
        void update(const InputHandler& input, bool colliding, Environment& environment) override {getInput(input); getMovement(input); applyPhysics(colliding, environment); move(); updateCrosshair(); updateHealthText();};
        void update(bool colliding, Environment& environment) {applyPhysics(colliding, environment); move(); updateCrosshair(); updateHealthText();};
        void collide();
        bool isDead() const { return health_ <= 0.0; }
        bool checkExplosion(const sf::CircleShape&, float);
        bool inControl(){return (state_ != unitState::falling);};
        float getShootAngle(){return aimAngle_;};
        sf::Vector2f getShootMomentum(sf::RenderWindow&);
        sf::Vector2f getPosition() const {return sprite_.getPosition();}; // Kanske måste tas bort då vi redan har getPos sen förut!?
        void setColor(sf::Color color){sprite_.setColor(color);}
        bool isShooting(){return shoot_;};
        void noShooting(){shoot_ = false; shootPower_ = false;};
        void draw(sf::RenderWindow&) override;
        float getHealth() const { return health_; }
        void giveHealth(float health) { health_ += health; }
};

class Projectile: public Entity{
    private:
        float wind_;
        Weapon* type_; // Variable to keep track of what kind of weapon it is
        float angle_;
        void getMovement(const InputHandler&);
        void applyPhysics(bool, Environment&) override;
        void move();
    public:
        Projectile(const sf::Texture& tex, const sf::Vector2f& pos, float spd, int mass, const sf::Vector2f& inMom, float wind, float angle, Weapon* weapon):
            Entity(tex, {pos.x, pos.y-1}, spd, mass), wind_{wind}, type_{weapon}, angle_{angle}{
                momentum_ = inMom;
                sprite_.setPosition(position_);
                if(angle == angle)
                    angle = angle;
            }
        bool isColliding(const Entity& entityObj) const;
        sf::CircleShape explode();
        float getDamage() const { return type_->getDamage(); }
};

#endif

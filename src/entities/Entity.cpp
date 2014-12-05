#include "Entity.hpp" 
#include "../utilities/InputHandler.hpp"
#include "../utilities/Assets.hpp"
#include <vector>
#include <cmath>
#include <string>

float toRadians(float degrees);
void Entity::move(){
    sprite_.setOrigin({(float)texture_.getSize().x/2, (float)texture_.getSize().y/2}); // Set origin to middle of sprite
    sprite_.move(momentum_); // Use sf::Sprite::move to move the sprite
    position_ = sprite_.getPosition(); // Get new position
}
void Entity::applyPhysics(bool colliding){
    if (!colliding) {
        momentum_.y += 1.5f;
    } else {
        /*momentum_.y = 0;
        if(momentum_.x > 0.2)
            momentum_.x = momentum_.x - 0.5;
        else if(momentum_.x < -0.2)
            momentum_.x = momentum_.x + 0.5;
        else
            momentum_.x = 0;
            */
        momentum_ = {0, -1};
    }
}
void Entity::getMovement(const InputHandler& input){
    if(input.isKeyPressed(sf::Keyboard::Key::Space))
        goto xkcd;
xkcd:
    return;
}
void Entity::draw(sf::RenderWindow& window){
    window.draw(sprite_);
}
void Entity::collide(){
}
void Unit::getInput(const InputHandler& input){
    shoot_ = false;
    if(state_ != unitState::falling && input.isKeyPressed(sf::Keyboard::Key::Space))
        state_ = unitState::shooting;
    else if(state_ != unitState::falling && input.isKeyReleased(sf::Keyboard::Key::Space))
        state_ = unitState::idle;
    if(input.isKeyPressed(sf::Keyboard::Key::Up)){
        if(!lookLeft_){
            aimAngle_ -= 5;
            if(aimAngle_ < -90)
                aimAngle_ = -90;
        }
        else if(lookLeft_){
            aimAngle_ += 5;
            if(aimAngle_ > 270)
                aimAngle_ = 270;
        }
    }
    if(input.isKeyPressed(sf::Keyboard::Key::Down)){
        if(!lookLeft_){
            aimAngle_ += 5;
            if(aimAngle_ > 90)
                aimAngle_ = 90;
        }
        else if(lookLeft_){
            aimAngle_ -= 5;
            if(aimAngle_ < 90)
                aimAngle_ = 90;
        }
    }
    if(state_ == unitState::shooting){
        ++shootPower_;
        if(shootPower_ > 100)
            state_ = unitState::idle;
    }
    if(state_ != unitState::shooting && shootPower_ != 0){
        shoot_ = true;
    }

    if(input.isKeyPressed(sf::Keyboard::Key::Num1))
        owner_->selectWeapon(0);
    if(input.isKeyPressed(sf::Keyboard::Key::Num2))
        owner_->selectWeapon(1);
    if(input.isKeyPressed(sf::Keyboard::Key::Num3))
        owner_->selectWeapon(2);

}
void Unit::getMovement(const InputHandler& input){
    if(state_ != unitState::falling){

        if (input.isKeyPressed(sf::Keyboard::Key::BackSpace)){ // To be changed to variable y coords
            state_ = unitState::falling;
            momentum_.y = -6.0f;
            if(lookLeft_)
                momentum_.x = -10.0f;
            else
                momentum_.x = 10.0f;
        } else { 
            if(momentum_.y < 0) 
                momentum_.y = momentum_.y * 0.99f; 
            if(abs(momentum_.y) < 0.10f) 
                momentum_.y = 0;
        }
        if (input.isKeyPressed(sf::Keyboard::Key::Left) && -momentum_.x <= maxMomentum_.x){
            momentum_.x += -speed_;
            if(!lookLeft_)
                aimAngle_ = (180 - aimAngle_);
            lookLeft_ = true; 
            sprite_.setScale(-1, 1);
        }
        else if (input.isKeyPressed(sf::Keyboard::Key::Left))
            momentum_.x = -maxMomentum_.x;
        if (input.isKeyPressed(sf::Keyboard::Key::Right) && momentum_.x <= maxMomentum_.x){
            momentum_.x += speed_;
            if(lookLeft_)
                aimAngle_ = 0 - (aimAngle_ - 180);
            lookLeft_ = false;
            sprite_.setScale(1, 1);
        }
        else if (input.isKeyPressed(sf::Keyboard::Key::Right) && momentum_.x <= maxMomentum_.x)
            momentum_.x = maxMomentum_.x;
    }
}
void Unit::applyPhysics(bool colliding){
    if(colliding)
        state_ = unitState::idle;

    Entity::applyPhysics(colliding);
}
void Unit::move(){
    Entity::move();
}
void Unit::updateCrosshair(){
    crosshair_.setPosition(sprite_.getPosition().x + 50*cos(toRadians(aimAngle_)), sprite_.getPosition().y + 50*sin(toRadians(aimAngle_)));
}
void Unit::collide(){
    state_ = unitState::idle;
    Entity::collide();
}
bool Unit::checkExplosion(const sf::CircleShape& expl, float damage) {
    float distanceX{expl.getPosition().x - getPos().x};
    float distanceY{expl.getPosition().y - getPos().y};
    float distance{std::sqrt(std::pow(distanceX, 2.0f) + std::pow(distanceY, 2.0f))};

    if (distance <= expl.getRadius()) {
        health_ -= damage * (distance / expl.getRadius());
        if (isDead()) {
            sprite_.setTexture(Assets::LOAD_TEXTURE("RIP.png"));
            crosshair_.setColor({0, 0, 0, 0});
        }

        momentum_.x -= (distanceX * ((expl.getRadius() * damage) / 32.0f)) / distance;
        momentum_.y -= (distanceY * ((expl.getRadius() * damage) / 32.0f)) / distance;
        return true;
    }

    return false;
}
void Unit::draw(sf::RenderWindow& window){
    window.draw(sprite_);
    window.draw(crosshair_);
}
sf::Vector2f Unit::getShootMomentum(sf::RenderWindow& screen){ 
    sf::Vector2f momentum;
    momentum.x = shootPower_ * cos(toRadians(aimAngle_));
    momentum.y = shootPower_ * sin(toRadians(aimAngle_));
    screen.setTitle("x: " + std::to_string(momentum.x) + " - y: " + std::to_string(momentum.y));
    shootPower_ = 0;
    return momentum;
}
void Projectile::applyPhysics(bool colliding){
    momentum_.x += wind_;
    Entity::applyPhysics(colliding);
}
void Projectile::move(){
    Entity::move();
}
void Projectile::getMovement(const InputHandler& input){
    if(input.isKeyPressed(sf::Keyboard::Key::Space))
        goto xkcd;
xkcd:
    ;
}

sf::CircleShape Projectile::explode(){
    removed_ = true;
    sf::CircleShape tempExplosion{type_->getExplosionRadius()};
    tempExplosion.setPosition(sprite_.getPosition());
    return tempExplosion;
}

float toRadians(float degrees){
    return (degrees * (3.14 / 180));
}

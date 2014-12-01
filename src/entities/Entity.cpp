#include "Entity.hpp" 
#include "../utilities/InputHandler.hpp" 
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
void Unit::getMovement(const InputHandler& input){
    shoot_ = false;
    if(state_ != unitState::falling){
        if(input.isKeyPressed(sf::Keyboard::Key::Space))
            state_ = unitState::shooting;
        else if(input.isKeyReleased(sf::Keyboard::Key::Space))
            state_ = unitState::idle;

        if(input.isKeyPressed(sf::Keyboard::Key::Up)){
            aimAngle_ -= 5;
        }
        if(input.isKeyPressed(sf::Keyboard::Key::Down)){
            aimAngle_ += 5;
        }
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
            lookLeft_ = true; 
        }
        else if (input.isKeyPressed(sf::Keyboard::Key::Left))
            momentum_.x = -maxMomentum_.x;
        if (input.isKeyPressed(sf::Keyboard::Key::Right) && momentum_.x <= maxMomentum_.x){
            momentum_.x += speed_;
            lookLeft_ = false;
        }
        else if (input.isKeyPressed(sf::Keyboard::Key::Right) && momentum_.x <= maxMomentum_.x)
            momentum_.x = maxMomentum_.x;
        if(!(position_.y < 400)){
            momentum_.x = momentum_.x * 0.85f;
            if(abs(momentum_.x) < 0.10f)
                momentum_.x = 0;
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
    crosshair_.setPosition(sprite_.getPosition().x + shootPower_*cos(toRadians(aimAngle_)), sprite_.getPosition().y + shootPower_*sin(toRadians(aimAngle_)));
}
void Unit::collide(){
    state_ = unitState::idle;
    Entity::collide();
}
void Unit::draw(sf::RenderWindow& window){
    window.draw(sprite_);
    window.draw(crosshair_);
}
sf::Vector2f Unit::getShootMomentum(sf::RenderWindow& screen){ 
    sf::Vector2f momentum;
    momentum.x = (crosshair_.getPosition().x - sprite_.getPosition().x);
    momentum.y = (crosshair_.getPosition().y - sprite_.getPosition().y);
    screen.setTitle("x: " + std::to_string(momentum.x) + " - y: " + std::to_string(momentum.y));
    shootPower_ = 0;
    return momentum;
}
void Projectile::applyPhysics(bool colliding){
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

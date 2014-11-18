#include "Entity.hpp"
#include "../utilities/InputHandler.hpp"
#include <vector>

//void Entity::getMovement(){;}
void Entity::move(){
    sprite_.setOrigin({(float)texture_.getSize().x/2,(float)texture_.getSize().y}); // Set origin to middle of sprite
    sprite_.move(momentum_); // Use sf::Sprite::move to move the sprite
    position_ = sprite_.getPosition(); // Get new position
}
void Entity::applyPhysics(){
    if(position_.y <= 400)
        momentum_.y += 1.5f;
    else if(momentum_.y > 0){
        momentum_.y = 0;
        position_.y = 401;
    }
}
void Entity::getMovement(const InputHandler& input){

}
void Entity::draw(sf::RenderWindow& window){
    window.draw(sprite_);
}
void Entity::collide(){
}
void Unit::getMovement(const InputHandler& input){
    if(state_ != unitState::falling){
        if (input.isKeyPressed(sf::Keyboard::Up) && position_.y >= 400){ // To be changed to variable y coords
            state_ = unitState::falling;
            momentum_.y = -20.0f;
            if(lookLeft_)
                momentum_.x = -10.0f;
            else
                momentum_.x = 10.0f;
            std::cout << "Up" << std::endl;
        } else { 
            if(momentum_.y < 0) 
                momentum_.y = momentum_.y * 0.99f; 
            if(abs(momentum_.y) < 0.10f) 
                momentum_.y = 0;
        }
        if (input.isKeyPressed(sf::Keyboard::Left) && -momentum_.x <= maxMomentum_.x){
            momentum_.x += -speed_;
            lookLeft_ = true; 
            std::cout << "Left, look at left?: " << lookLeft_ << std::endl;
        }
        else if (input.isKeyPressed(sf::Keyboard::Left))
            momentum_.x = -maxMomentum_.x;
        if (input.isKeyPressed(sf::Keyboard::Right) && momentum_.x <= maxMomentum_.x){
            momentum_.x += speed_;
            lookLeft_ = false;
            std::cout << "Right, look at left?: " << lookLeft_ << std::endl;
        }
        else if (input.isKeyPressed(sf::Keyboard::Right) && momentum_.x <= maxMomentum_.x)
            momentum_.x = maxMomentum_.x;
        if(!(position_.y < 400)){
            momentum_.x = momentum_.x * 0.85f;
            if(abs(momentum_.x) < 0.10f)
                momentum_.x = 0;
        }
    }
    std::cout << ((state_ == unitState::falling) ? ("falling") : ("idle")) << std::endl;
}

void Unit::applyPhysics(){
    Entity::applyPhysics();
}
void Unit::move(){
    Entity::move();
}    
void Unit::collide(){
    state_ = unitState::idle;
    Entity::collide();
}
void Projectile::applyPhysics(){
    if(momentum_.y < -40)
        momentum_.y = -40;

    momentum_.y += 1.5f;

    if(momentum_.x > 8)
        momentum_.x = 8;
    else if(momentum_.x < -8)
        momentum_.x = -8;
    Entity::applyPhysics();
}
void Projectile::move(){
    sprite_.setOrigin({(float)texture_.getSize().x/2,(float)texture_.getSize().y});
    Entity::move();
}
void Projectile::getMovement(const InputHandler& input){
}

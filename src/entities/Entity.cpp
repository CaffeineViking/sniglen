#ifndef ENTITIES_CPP
#define ENTITIES_CPP

#include "Entity.hpp"
#include <vector>

//void Entity::getMovement(){;}
void Entity::move(){
    sprite_.setOrigin({(float)texture_.getSize().x/2,(float)texture_.getSize().y});
    sprite_.move(momentum_);
    position_ = sprite_.getPosition();
}
void Entity::applyPhysics(){
    if(position_.y <= 500)
        momentum_.y += 1.5f;
    else if(momentum_.y > 0)
        momentum_.y = 0;
}
void Unit::getMovement(){
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && position_.y >= 500){ //500 To be changed to variable y coords
        momentum_.y = -20.0f; 
    } else { 
        if(momentum_.y < 0) 
            momentum_.y = momentum_.y * 0.99f; 
        if(abs(momentum_.y) < 0.10f) 
            momentum_.y = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && -momentum_.x <= maxMomentum_.x) {
        position_ += {-speed_*2, 0.0f};
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && momentum_.x <= maxMomentum_.x) {
        position_ += {speed_*2, 0.0f};
    } else{
        momentum_.x = momentum_.x * 0.85f;
        if(abs(momentum_.x) < 0.10f)
            momentum_.x = 0;
    }

    if(position_.y > 500){
        position_.y = 501;
    }
    sprite_.setPosition(position_);
}

void Unit::applyPhysics(){
    Entity::applyPhysics();
}
void Unit::move(){
    Entity::move();
}
void Projectile::update(){
    getMovement();
    applyPhysics();
    move();
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

#endif

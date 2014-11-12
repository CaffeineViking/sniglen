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
    else if(momentum_.y > 0){
        momentum_.y = 0;
        position_.y = 501;
    }
}
void Entity::getMovement(){

}
void Entity::draw(sf::RenderWindow& window){
    window.draw(sprite_);
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && -momentum_.x <= maxMomentum_.x)
        momentum_.x += -speed_;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	    momentum_.x = -maxMomentum_.x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && momentum_.x <= maxMomentum_.x)
        momentum_.x += speed_;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && momentum_.x <= maxMomentum_.x)
	    momentum_.x = maxMomentum_.x;
    if(!(position_.y < 500)){
    	momentum_.x = momentum_.x * 0.85f;
    	if(abs(momentum_.x) < 0.10f)
        	momentum_.x = 0;
    }
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
void Projectile::getMovement(){
}

#endif

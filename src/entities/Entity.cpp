#include "Entity.hpp" 

#include "../utilities/InputHandler.hpp" 
#include "../environment/Terrain.hpp"
#include "../environment/Environment.hpp"
#include "../utilities/Assets.hpp"

#include <vector>
#include <cmath>
#include <string>

#include <iostream>

float toRadians(float degrees);
void Entity::move(){
    sprite_.setOrigin({(float)texture_.getSize().x/2, (float)texture_.getSize().y/2}); // Set origin to middle of sprite
    sprite_.move(momentum_); // Use sf::Sprite::move to move the sprite
    position_ = sprite_.getPosition(); // Get new position
}
void Entity::applyPhysics(bool colliding, Environment& environment){
    /*if (!colliding) {
        momentum_.y += 1.5f;
    } else {

        momentum_ = {0, -1};
    }*/

    momentum_.y += 1.5f;
}
void Entity::getMovement(const InputHandler&){
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
    if(state_ == unitState::shooting && owner_->getCurrentWeaponAmmo() > 0){
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
void Unit::applyPhysics(bool colliding, Environment& environment){
    /*int timesMoved = 0;	
    // Make a copy of unit to check collision on next frame

    // Move one pixel at a time on y-axis until you have moved for what it should move
    while(timesMoved < abs(momentum_.y)){
        // Check for collision each of those times
        if(!environment.getTerrain().isColliding(*temp)){
            // If not colliding, move in the appropriate direction one pixel, set unit to be falling and increment variable for amount of movement done
            if(momentum_.y > 0)
                temp->sprite_.move({0.0f, 1.0f});
            else 
                temp->sprite_.move({0.0f, -1.0f});
            ++timesMoved;
            state_ = unitState::falling;
        } else {
            // If collision is detected, move one pixel back and remove momentum in y-axis, then set state to idle and break
            if(momentum_.y < 0)
                temp->sprite_.move({0.0f, 1.0f});
            else 
                temp->sprite_.move({0.0f, -1.0f});
            momentum_.y = 0;
            state_ = unitState::idle;
            break;
        }
    }

    // Check pixel below if we should fall or not
    temp->sprite_.move({0.0f, 1.0f});
    if(!environment.getTerrain().isColliding(*temp))
        state_ = unitState::falling;
    temp->sprite_.move({0.0f, -1.0f});

    // Apply gravity if falling
    if(state_ == unitState::falling)
        momentum_.y += 1.5;

    // Reset move counter
    timesMoved = 0;

    // Move one pixel at a time on x-axis until you have moved for what it should move
    while(timesMoved < abs(momentum_.x)){
        // Check for collision each of those times
        if(!environment.getTerrain().isColliding(*temp)){
            // If not colliding, move in the appropriate direction one pixel, increment variable for amount of movement done
            if(momentum_.x > 0)
                temp->sprite_.move({1.0f, 0.0f});
            else 
                temp->sprite_.move({-1.0f, 0.0f});
            ++timesMoved;
        } else {
            // If collision is detected, check if the slope is small enough
            timesMoved = 0;
            while(environment.getTerrain().isColliding(*temp)){
                temp->sprite_.move({0.0f, -1.0f});
                ++timesMoved;
            }
            // If it's too high, shove it back on the x-axis
            if(timesMoved > 30){
                if(momentum_.x < 0)
                    temp->sprite_.move({1.0f, 0.0f});
                else 
                    temp->sprite_.move({-1.0f, 0.0f});
            } else {
                // If it low enough, push him upwards to be on top of the pixels
                momentum_.x = 0.0f;
                momentum_.y = 0.0f;
                temp->sprite_.move({timesMoved, 0});
            }

            // Apply friction and stop if momentum is too low
            if(momentum_.x < -0.2f)
                momentum_.x *= 0.6f;
            else if(momentum_.x > 0.2f)
                momentum_.x *= 0.6f;
            else
                momentum_.x = 0.0f;
            break;
        }
    }*/
    //if(state_ != unitState::falling){
    //if(momentum_.x != 0 && colliding){
    //	temp->sprite_.move({0.0f, -1.0f});
    //	timesMoved = 0;
    //	temp->sprite_.move({momentum_.x, 0.0f});
    //	while(environment.getTerrain().isColliding(*temp)){
    //		temp->sprite_.move({0.0f, -1.0f});
    //		++timesMoved;
    //	}

    //	if(timesMoved < 30){
    //		this->sprite_.setPosition(temp->sprite_.getPosition());
    //	}
    //	else{
    //		momentum_.x = 0.0f;
    //		momentum_.y = 0.0f;
    //	}
    //	
    //	if(momentum_.x < -0.2f)
    //		momentum_.x *= 0.6f;
    //	else if(momentum_.x > 0.2f)
    //		momentum_.x *= 0.6f;
    //	else
    //		momentum_.x = 0.0f;
    //	
    //	if(!colliding)
    //		momentum_.y += 1.5f;
    //	else
    //		state_ = unitState::idle;
    //} 
    //else if (momentum_.y != 0 || state_ == unitState::falling){
    //    float distance = std::sqrt(std::pow(momentum_.x, 2.0f) + std::pow(momentum_.y, 2.0f));
    //    if(environment.getTerrain().isColliding(*temp)){
    //        temp->sprite_.move({momentum_.x, momentum_.y});
    //        while(environment.getTerrain().isColliding(*temp)){
    //            temp->sprite_.move({-momentum_.x/distance, -momentum_.y/distance});
    //			if(!environment.getTerrain().isColliding(*temp)){
    //				momentum_.y = -1.5f;
    //				state_ = unitState::idle;
    //			}	
    //		}
    //    }
    //    momentum_.y += 1.5;
    //}

    // Apply the changes done onto the real unit
    // this->sprite_.setPosition(temp->sprite_.getPosition());
    // delete temp;

    // TODO: Move this interface to move procedure, need to add environment reference.
    // Check if we need to find closest collision point.

    Unit* temp = new Unit{*sprite_.getTexture(), *crosshair_.getTexture(), sprite_.getPosition(), speed_, mass_, nullptr};
    temp->sprite_.move(momentum_);
    while(environment.getTerrain().isColliding(*temp)) {
        /*if(environment.getTerrain().goLeftRightCheckSlope(this->getPosition()) == std::make_pair(false, true)) {
            temp->sprite_.move(1, 0);
            std::cout << "left" << std::endl;
        }
        if(environment.getTerrain().goLeftRightCheckSlope(this->getPosition()) == std::make_pair(true, false)) {
            temp->sprite_.move(-1, 0);
            std::cout << "right" << std::endl;
        }*/
        temp->sprite_.move(0, -1);
        colliding = true;
        state_ = unitState::idle;
    }

    momentum_ = temp->getPosition() - this->getPosition();
    delete temp;

    if (!colliding) {
        momentum_.y += 1.5f;
        state_ = unitState::falling;
    } else {
        momentum_.x *= 0.85f;
    }
    Entity::applyPhysics(colliding, environment);
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
            setTexture(Assets::LOAD_TEXTURE("RIP.png"));
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
    window.draw(healthText_);
}
sf::Vector2f Unit::getShootMomentum(sf::RenderWindow& screen){ 
    sf::Vector2f momentum;
    momentum.x = shootPower_ * cos(toRadians(aimAngle_));
    momentum.y = shootPower_ * sin(toRadians(aimAngle_));
    screen.setTitle("x: " + std::to_string(momentum.x) + " - y: " + std::to_string(momentum.y));
    shootPower_ = 0;
    return momentum;
}
void Unit::updateHealthText(){
    healthText_.setString(std::to_string((int)std::ceil(health_)));
    healthText_.setOrigin({healthText_.getLocalBounds().width/2, healthText_.getLocalBounds().height/2});
    healthText_.setPosition({sprite_.getPosition().x, sprite_.getPosition().y - 50});
}
void Projectile::applyPhysics(bool colliding, Environment& environment){
    momentum_.x += wind_;
    Entity::applyPhysics(colliding, environment);
}
void Projectile::move(){
    Entity::move();
}
void Projectile::getMovement(const InputHandler&){
}

sf::CircleShape Projectile::explode(){
    removed_ = true;
    sf::CircleShape tempExplosion{type_->getExplosionRadius()};
    tempExplosion.setPosition(sprite_.getPosition());
    return tempExplosion;
}

bool Projectile::isColliding(const Entity& entityObj) const {
    float vectorX = this->getPos().x - entityObj.getPos().x;
    float vectorY = this->getPos().y - entityObj.getPos().y;
    float result = std::sqrt(std::pow(vectorX, 2.0f) + std::pow(vectorY, 2.0f));
    float constToCompareWith = (float)(entityObj.getSpriteData().getSize().x/2 + this->getSpriteData().getSize().x/2);
    if(result <= constToCompareWith)
        return true;
    return false;
}

float toRadians(float degrees){
    return (degrees * (3.14 / 180));
}

#ifndef WEAPONS_HPP
#define WEAPONS_HPP

class Weapon {
private:
    int damage_;
    float explosionRadius_;

public:
    Weapon(int damage, float explosionRadius) :
        damage_{damage}, explosionRadius_{explosionRadius} {}

    int getDamage() const { return damage_; }
    float getExplosionRadius() const { return explosionRadius_; }
};

class Bazooka: public Weapon {
public:
    Bazooka() : Weapon{10, 20.0} {}
};

#endif

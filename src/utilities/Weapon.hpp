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
    Bazooka() : Weapon{10, 40.0} {}
};

class MiniBaz: public Weapon {
public:
    MiniBaz(): Weapon{50, 5.0} {}
};

class Nuke: public Weapon {
public:
    Nuke(): Weapon{5, 250.0} {}
};
#endif

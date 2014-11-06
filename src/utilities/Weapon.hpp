#ifndef WEAPONS_HPP
#define WEAPONS_HPP

class Weapon{
    public:
        int damage_;
        int blastRadius_;
        Weapon(int dmg = 1, int rad = 20):
            damage_{dmg}, blastRadius_{rad}{}
};

class Bazooka: public Weapon{
    public:
        using Weapon::Weapon;
};
#endif

#include "Weapon.hpp"
#include <iostream>


Weapon::Weapon()
    : Item(), damage(0) {}


Weapon::Weapon(std::string name, Rarities rarity, float price, int damage)
    : Item(name, rarity, price), damage(damage) {}


Weapon::Weapon(std::string name, Rarities rarity, float price, SDL_Texture* texture, int damage)
    : Item(name, rarity, price, texture), damage(damage) {}

// Getter
int Weapon::getDamage() const {
    return damage;
}

// Setter
void Weapon::setDamage(int damage) {
    this->damage = damage;
}
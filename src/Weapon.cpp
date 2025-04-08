#include <Weapon.hpp>

#include <iostream>
#include <SDL2/SDL.h>

Weapon::Weapon()
    : Item(), damage(0) {}

Weapon::Weapon(std::string name, Rarities rarity, float price, int damage)
    : Item(name, rarity, price), damage(damage) {}

Weapon::Weapon(std::string name, Rarities rarity, float price, SDL_Texture *texture, int damage)
    : Item(name, rarity, price, texture), damage(damage) {}

Weapon::~Weapon()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

// Getter
int Weapon::getDamage() const
{
    return damage;
}

// Setter
void Weapon::setDamage(int damage)
{
    this->damage = damage;
}

void Weapon::display()
{
    Item::display();
    std::cout << "Damage: " << this->damage << std::endl;
}

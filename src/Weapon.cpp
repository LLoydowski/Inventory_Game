#include <Weapon.hpp>

#include <iostream>
#include <SDL2/SDL.h>
#include <sstream>
#include <iomanip>

Weapon::Weapon()
    : Item(), damage(0)
{
    this->type = ItemType::Weapon;
}

Weapon::Weapon(std::string name, Rarities rarity, float price, int damage)
    : Item(name, rarity, price), damage(damage)
{
    this->type = ItemType::Weapon;
}

Weapon::Weapon(std::string name, Rarities rarity, float price, SDL_Texture *texture, int damage)
    : Item(name, rarity, price, texture), damage(damage)
{
    this->type = ItemType::Weapon;
}

Weapon::~Weapon()
{
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

std::string Weapon::getInfo()
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << this->damage;
    std::string dmgString = stream.str();

    std::string text = "Damage: +" + dmgString;

    return text;
}

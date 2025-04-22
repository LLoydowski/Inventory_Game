#include <Weapon.hpp>

#include <iostream>
#include <SDL2/SDL.h>
#include <sstream>
#include <iomanip>

Weapon::Weapon()
    : Item(), DMG(0)
{
    this->type = ItemType::Weapon;
}

Weapon::Weapon(std::string name, Rarities rarity, float price, int damage)
    : Item(name, rarity, price), DMG(damage)
{
    this->type = ItemType::Weapon;
}

Weapon::Weapon(std::string name, Rarities rarity, float price, SDL_Texture *texture, int damage)
    : Item(name, rarity, price, texture), DMG(damage)
{
    this->type = ItemType::Weapon;
}

Weapon::~Weapon()
{
}

// Getter
float Weapon::getDamage()
{
    return DMG;
}

// Setter
void Weapon::setDamage(float damage)
{
    this->DMG = damage;
}

void Weapon::display()
{
    Item::display();
    std::cout << "Damage: " << this->DMG << std::endl;
}

std::string Weapon::getInfo()
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << this->DMG;
    std::string dmgString = stream.str();

    std::string text = "Damage: +" + dmgString;

    return text;
}

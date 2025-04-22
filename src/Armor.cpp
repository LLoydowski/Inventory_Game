#include <Armor.hpp>

#include <iostream>
#include <SDL2/SDL.h>
#include <Enums.hpp>

#include <sstream>
#include <iomanip>

Armor::Armor()
    : Item(), DEF(0)
{
    this->type = ItemType::Armor;
}

Armor::Armor(std::string name, Rarities rarity, float price, int defense)
    : Item(name, rarity, price), DEF(defense)
{
    this->type = ItemType::Armor;
}

Armor::Armor(std::string name, Rarities rarity, float price, SDL_Texture *texture, int defense)
    : Item(name, rarity, price, texture), DEF(defense)
{
    this->type = ItemType::Armor;
}

Armor::~Armor()
{
}

// Getter
float Armor::getDEF()
{
    return DEF;
}

// Setter
void Armor::setDEF(float defense)
{
    this->DEF = defense;
}

void Armor::display()
{
    Item::display();
    std::cout << "Defence: " << this->DEF << std::endl;
}

std::string Armor::getInfo()
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << this->DEF;
    std::string defString = stream.str();

    std::string text = "Defense: +" + defString;

    return text;
}

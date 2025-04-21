#include <Armor.hpp>

#include <iostream>
#include <SDL2/SDL.h>
#include <Enums.hpp>

#include <sstream>
#include <iomanip>

Armor::Armor()
    : Item(), defense(0)
{
    this->type = ItemType::Armor;
}

Armor::Armor(std::string name, Rarities rarity, float price, int defense)
    : Item(name, rarity, price), defense(defense)
{
    this->type = ItemType::Armor;
}

Armor::Armor(std::string name, Rarities rarity, float price, SDL_Texture *texture, int defense)
    : Item(name, rarity, price, texture), defense(defense)
{
    this->type = ItemType::Armor;
}

Armor::~Armor()
{
}

// Getter
int Armor::getDefense() const
{
    return defense;
}

// Setter
void Armor::setDefense(int defense)
{
    this->defense = defense;
}

void Armor::display()
{
    Item::display();
    std::cout << "Defence: " << this->defense << std::endl;
}

std::string Armor::getInfo()
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << this->defense;
    std::string defString = stream.str();

    std::string text = "Defense: +" + defString;

    return text;
}

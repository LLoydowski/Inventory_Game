#include <Trinket.hpp>

#include <iostream>
#include <SDL2/SDL.h>
#include <sstream>
#include <iomanip>

Trinket::Trinket()
    : Item()
{
    this->type = ItemType::Trinket;
}

// Konstruktor bez tekstury
Trinket::Trinket(std::string name, Rarities rarity, float price, float HP)
    : Item(name, rarity, price), HP{HP}
{
    this->type = ItemType::Trinket;
}

// Konstruktor z teksturą
Trinket::Trinket(std::string name, Rarities rarity, float price, SDL_Texture *texture)
    : Item(name, rarity, price, texture)
{
    this->type = ItemType::Trinket;
}

Trinket::~Trinket()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

float Trinket::getAdditionalHP()
{
    return HP;
}

void Trinket::display()
{
    Item::display();
    std::cout << "Attribute: --NONE--" << std::endl;
}

std::string Trinket::getInfo()
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << this->HP;
    std::string dmgString = stream.str();

    std::string text = "HP: +" + dmgString;

    return text;
}

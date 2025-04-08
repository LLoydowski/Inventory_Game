#include <Trinket.hpp>

#include <iostream>
#include <SDL2/SDL.h>

Trinket::Trinket()
    : Item() {}

// Konstruktor bez tekstury
Trinket::Trinket(std::string name, Rarities rarity, float price)
    : Item(name, rarity, price) {}

// Konstruktor z teksturą
Trinket::Trinket(std::string name, Rarities rarity, float price, SDL_Texture *texture)
    : Item(name, rarity, price, texture) {}

Trinket::~Trinket()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
    }
}

void Trinket::display()
{
    Item::display();
    std::cout << "Attribute: --NONE--" << std::endl;
}

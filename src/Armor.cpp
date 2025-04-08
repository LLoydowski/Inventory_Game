#include <Armor.hpp>

#include <iostream>
#include <SDL2/SDL.h>

Armor::Armor()
    : Item(), defense(0) {}

Armor::Armor(std::string name, Rarities rarity, float price, int defense)
    : Item(name, rarity, price), defense(defense) {}

Armor::Armor(std::string name, Rarities rarity, float price, SDL_Texture *texture, int defense)
    : Item(name, rarity, price, texture), defense(defense) {}

Armor::~Armor()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
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

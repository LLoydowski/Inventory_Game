#pragma once

#include "Item.hpp"
#include <string>

class Trinket : public Item
{

public:
    Trinket();
    Trinket(std::string name, Rarities rarity, float price);
    Trinket(std::string name, Rarities rarity, float price, SDL_Texture *texture);
    ~Trinket() override;

    void display() override;
};

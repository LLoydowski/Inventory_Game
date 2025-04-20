#pragma once

#include "Item.hpp"
#include <string>

class Trinket : public Item
{
private:
    float HP;

public:
    Trinket();
    Trinket(std::string name, Rarities rarity, float price, float HP);
    Trinket(std::string name, Rarities rarity, float price, SDL_Texture *texture);
    ~Trinket() override;

    float getAdditionalHP();

    void display() override;
};

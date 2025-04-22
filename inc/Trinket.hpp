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
    Trinket(std::string name, Rarities rarity, float price, SDL_Texture *texture, float HP);
    ~Trinket();
    float getAdditionalHP();

    void display() override;

    std::string getInfo() override;
};

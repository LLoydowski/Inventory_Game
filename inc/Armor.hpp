#pragma once

#include "Item.hpp"
#include <string>

class Armor : public Item
{
private:
    float DEF;

public:
    Armor();
    Armor(std::string name, Rarities rarity, float price, int defense);
    Armor(std::string name, Rarities rarity, float price, SDL_Texture *texture, int defense);
    ~Armor();

    // Getters
    float getDEF();

    // Setters
    void setDEF(float defense);

    void display() override;

    std::string getInfo() override;
};

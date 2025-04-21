#pragma once

#include "Item.hpp"
#include <string>

class Armor : public Item
{
private:
    int defense;

public:
    Armor();
    Armor(std::string name, Rarities rarity, float price, int defense);
    Armor(std::string name, Rarities rarity, float price, SDL_Texture *texture, int defense);
    ~Armor();

    // Getters
    int getDefense() const;

    // Setters
    void setDefense(int defense);

    void display() override;

    std::string getInfo() override;
};

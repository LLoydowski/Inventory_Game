#pragma once

#include "Item.hpp"
#include <string>

class Weapon : public Item
{
private:
    float DMG;

public:
    Weapon();
    Weapon(std::string name, Rarities rarity, float price, int damage);
    Weapon(std::string name, Rarities rarity, float price, SDL_Texture *texture, int damage);
    ~Weapon();

    // Getters
    float getDamage();

    // Setters
    void setDamage(float damage);

    void display() override;

    std::string getInfo() override;
};

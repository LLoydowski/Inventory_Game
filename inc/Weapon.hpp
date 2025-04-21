#pragma once

#include "Item.hpp"
#include <string>

class Weapon : public Item
{
private:
    int damage;

public:
    Weapon();
    Weapon(std::string name, Rarities rarity, float price, int damage);
    Weapon(std::string name, Rarities rarity, float price, SDL_Texture *texture, int damage);
    ~Weapon();

    // Getters
    int getDamage() const;

    // Setters
    void setDamage(int damage);

    void display() override;

    std::string getInfo() override;
};

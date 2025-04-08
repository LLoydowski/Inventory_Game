#pragma once

#include "Item.hpp"
#include <string>

class Potion : public Item
{
private:
    int hp;
    int attack;
    int defense;

public:
    Potion();
    Potion(std::string name, Rarities rarity, float price, int hp, int attack, int defense);
    Potion(std::string name, Rarities rarity, float price, SDL_Texture *texture, int hp, int attack, int defense);
    ~Potion() override;

    // Getters
    int getHp() const;
    int getAttack() const;
    int getDefense() const;

    // Setters
    void setHp(int hp);
    void setAttack(int attack);
    void setDefense(int defense);

    void display() override;
};

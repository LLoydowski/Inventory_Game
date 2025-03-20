#pragma once

#include <string>
#include <iostream>

enum Rarities
{
    common,
    uncommon,
    rare,
    epic
};

class Item
{
private:
    std::string name;
    Rarities rarity;
    float price;
    bool favourite;

public:
    Item();
    Item(std::string name, Rarities rarity, float price);

    void display();

    // Getters
    std::string getName();
    float getPrice();
    Rarities getRarity();
    bool getFavourite();
};
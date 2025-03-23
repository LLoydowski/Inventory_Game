#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

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
    SDL_Texture *texture;

public:
    Item();
    Item(std::string name, Rarities rarity, float price);
    Item(std::string name, Rarities rarity, float price, SDL_Texture *texture);

    void display();

    // Getters
    std::string getName();
    SDL_Texture *getTexture();

    // Setters
    void setTexture(SDL_Texture *texture);
};
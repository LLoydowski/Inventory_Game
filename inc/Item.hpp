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
    bool favourite;
    SDL_Texture *texture;

public:
    Item();
    Item(std::string name, Rarities rarity, float price);
    Item(std::string name, Rarities rarity, float price, SDL_Texture *texture);
    virtual ~Item(); 

    virtual void display();

    // Getters
    std::string getName();

    float getPrice();
    Rarities getRarity();
    bool getFavourite();
    SDL_Texture *getTexture();

    // Setters
    void setFavourite(bool optoion);
    void setTexture(SDL_Texture *texture);
};
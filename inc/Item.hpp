#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

#include <Enums.hpp>

class Item
{
protected:
    std::string name;
    Rarities rarity;
    float price;
    bool favourite;
    SDL_Texture *texture;
    ItemType type = ItemType::Generic;
    int tier;

public:
    Item();
    Item(std::string name, Rarities rarity, float price);
    Item(std::string name, Rarities rarity, float price, SDL_Texture *texture);
    virtual ~Item();

    virtual void display();

    virtual Item *copy();

    //? Getters
    std::string getName();

    float getPrice();
    Rarities getRarity();
    bool getFavourite();
    SDL_Texture *getTexture();
    ItemType getType();
    virtual std::string getInfo();
    int getTier();

    //? Setters
    void setFavourite(bool optoion);
    void setTexture(SDL_Texture *texture);
    void setTier(int tier);
};
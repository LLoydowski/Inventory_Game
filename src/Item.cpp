#include <Item.hpp>

#include <string>
#include <iostream>

#include <sstream>
#include <iomanip>

Item::Item() : name{"Scrap"}, rarity{Rarities::common}, price{0.1}, favourite{false}, texture{nullptr}
{
}

Item::Item(std::string name, Rarities rarity, float price) : name{name}, rarity{rarity}, price{price}, favourite{false}, texture{nullptr}
{
}

Item::Item(std::string name, Rarities rarity, float price, SDL_Texture *texture) : name{name}, rarity{rarity}, price{price}, favourite{false}, texture{texture}
{
}

Item::~Item()
{
    // if (texture)
    // {
    //     SDL_DestroyTexture(texture);
    // }
}

void Item::display()
{
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Price: " << int(this->rarity) << std::endl;
    std::cout << "Rarity: " << this->price << std::endl;
    std::cout << "Favoutire" << this->favourite << std::endl;
}

//! Getters
std::string Item::getName()
{
    return name;
}

Item *Item::copy()
{
    Item *newItem = new Item(*this);

    return newItem;
}

float Item::getPrice()
{
    return price;
}

Rarities Item::getRarity()
{
    return rarity;
}

bool Item::getFavourite()
{
    return favourite;
}

SDL_Texture *Item::getTexture()
{
    return texture;
}
ItemType Item::getType()
{
    return type;
}
std::string Item::getInfo()
{
    // std::stringstream stream;
    // stream << std::fixed << std::setprecision(1) << this->();
    // std::string priceString = stream.str();
    std::string text = "";

    return text;
}
//? Setters

void Item::setFavourite(bool optoion)
{
    favourite = optoion;
}

void Item::setTexture(SDL_Texture *texture)
{
    this->texture = texture;
}

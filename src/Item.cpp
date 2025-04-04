#include <Item.hpp>

#include <string>
#include <iostream>

Item::Item() : name{"Scrap"}, rarity{common}, price{0.1}, favourite{false}, texture{nullptr}
{
}

Item::Item(std::string name, Rarities rarity, float price) : name{name}, rarity{rarity}, price{price}, favourite{false}, texture{nullptr}
{
}

Item::Item(std::string name, Rarities rarity, float price, SDL_Texture *texture) : name{name}, rarity{rarity}, price{price}, favourite{false}, texture{texture}
{
}

Item::~Item() {

}

void Item::display()
{
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Price: " << this->rarity << std::endl;
    std::cout << "Rarity: " << this->price << std::endl;
    std::cout << "Favoutire" << this->favourite << std::endl;
}

//! Getters
std::string Item::getName()
{
    return name;
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
//! Setters

void Item::setFavourite(bool optoion)
{
    favourite = optoion;
}

void Item::setTexture(SDL_Texture *texture)
{
    this->texture = texture;
}

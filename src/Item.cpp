#include <Item.hpp>

#include <string>
#include <iostream>

Item::Item() : name{"Scrap"}, rarity{common}, price{0.1}, favourite{false}
{
}

Item::Item(std::string name, Rarities rarity, float price) : name{name}, rarity{rarity}, price{price}, favourite{false}
{
}

void Item::display()
{
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Price: " << this->rarity << std::endl;
    std::cout << "Rarity: " << this->price << std::endl;
    std::cout << "Favoutire" << this->favourite << std::endl;
}

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

}
#include "Trinket.hpp"
#include <iostream>

Trinket::Trinket()
    : Item() {}

// Konstruktor bez tekstury
Trinket::Trinket(std::string name, Rarities rarity, float price)
    : Item(name, rarity, price) {}

// Konstruktor z teksturą
Trinket::Trinket(std::string name, Rarities rarity, float price, SDL_Texture* texture)
    : Item(name, rarity, price, texture) {}

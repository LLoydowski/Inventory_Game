#include "Chest.hpp"

Chest::~Chest()
{
    for (int i = 0; i < lootTable.size(); i++)
    {
        delete lootTable[i];
        lootTable[i] = nullptr;
    }
    lootTable.clear();
}

Chest::Chest() : Item()
{
}

Chest::Chest(std::string name, Rarities rarity, float price)
    : Item(name, rarity, price)
{
}

Chest::Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture)
    : Item(name, rarity, price, texture)
{
}

Chest::Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture, std::vector<Item *> lootTable)
    : Item(name, rarity, price, texture)
{
    this->lootTable = lootTable;
}

Item *Chest::openChest()
{

    return nullptr;
}

void Chest::setLootTable(std::vector<Item *> table)
{
    this->lootTable = table;
}
std::vector<Item *> *Chest::getLootTable()
{
    return &lootTable;
}

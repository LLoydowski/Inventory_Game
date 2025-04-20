#pragma once

#include <Item.hpp>
#include <vector>

#include <LootTable.hpp>

class Chest : public Item
{
private:
    LootTable *lootTable;
    std::string type = "Chest";

public:
    ~Chest();

    Chest();
    Chest(std::string name, Rarities rarity, float price);
    Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture);
    Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture, LootTable *lootTable);

    Item *openChest();

    //? Setters
    void setLootTable(LootTable *table);

    //? Getters
    LootTable *getLootTable();
};
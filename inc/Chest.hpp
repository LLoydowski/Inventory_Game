#pragma once

#include <Item.hpp>
#include <vector>

#include <LootTable.hpp>

class Chest : public Item
{
private:
    LootTable *lootTable;

public:
    Chest();
    Chest(std::string name, Rarities rarity, float price);
    Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture);
    Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture, LootTable *lootTable);
    ~Chest();

    Item *openChest();
    Item *copy() override;

    //? Setters
    void setLootTable(LootTable *table);

    //? Getters
    LootTable *getLootTable();
};
#pragma once

#include <Item.hpp>
#include <vector>

class Chest : public Item
{
private:
    std::vector<Item *> lootTable;
    std::string type = "Chest";

public:
    ~Chest();

    Chest();
    Chest(std::string name, Rarities rarity, float price);
    Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture);
    Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture, std::vector<Item *> lootTable);

    virtual Item *openChest();

    //? Setters
    void setLootTable(std::vector<Item *> table);

    //? Getters
    std::vector<Item *> *getLootTable();
};
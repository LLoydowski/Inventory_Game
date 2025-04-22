#include "Chest.hpp"
#include <Weapon.hpp>
#include <Armor.hpp>
#include <Trinket.hpp>

Chest::~Chest()
{
    delete lootTable;
}

Chest::Chest() : Item()
{
    this->type = ItemType::Chest;
    this->tier = 1;
}

Chest::Chest(std::string name, Rarities rarity, float price)
    : Item(name, rarity, price)
{
    this->type = ItemType::Chest;
    this->tier = 1;
}

Chest::Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture)
    : Item(name, rarity, price, texture)
{
    this->type = ItemType::Chest;
    this->tier = 1;
}

Chest::Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture, LootTable *lootTable)
    : Item(name, rarity, price, texture)
{
    this->lootTable = lootTable;
    this->type = ItemType::Chest;
    this->tier = 1;
}

Item *Chest::openChest()
{
    GeneratedStats stats = lootTable->generate();
    Item *item = nullptr;

    std::string textureID = "";

    if (stats.itemType == ItemType::Weapon)
    {
        textureID = "Sword0" + std::to_string(tier);
        item = new Weapon("Sword", stats.rarity, 0, loadedTextures[textureID], stats.additionalDMG);
    }
    else if (stats.itemType == ItemType::Armor)
    {
        textureID = "Armor0" + std::to_string(tier);
        item = new Armor("Armor", stats.rarity, 0, loadedTextures[textureID], stats.additionalDEF);
    }
    else if (stats.itemType == ItemType::Trinket)
    {
        textureID = "Trinket0" + std::to_string(tier);
        item = new Trinket("Ammulet", stats.rarity, 0, loadedTextures[textureID], stats.additionalHP);
    }

    return item;
}

void Chest::setLootTable(LootTable *table)
{
    this->lootTable = table;
}

LootTable *Chest::getLootTable()
{
    return lootTable;
}

Item *Chest::copy()
{
    LootTable *newLootTable = new LootTable(*this->lootTable);

    Chest *chest = new Chest(*this);

    chest->setLootTable(newLootTable);

    return chest;
}

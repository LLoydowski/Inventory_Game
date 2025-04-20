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
}

Chest::Chest(std::string name, Rarities rarity, float price)
    : Item(name, rarity, price)
{
    this->type = ItemType::Chest;
}

Chest::Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture)
    : Item(name, rarity, price, texture)
{
    this->type = ItemType::Chest;
}

Chest::Chest(std::string name, Rarities rarity, float price, SDL_Texture *texture, LootTable *lootTable)
    : Item(name, rarity, price, texture)
{
    this->lootTable = lootTable;
    this->type = ItemType::Chest;
}

Item *Chest::openChest()
{
    GeneratedStats stats = lootTable->generate(); //! <- Error here
    Item *item = nullptr;

    if (stats.itemType == ItemType::Weapon)
    {
        item = new Weapon("Sword", stats.rarity, 0, loadedTextures["Sword01"], stats.additionalDMG);
    }
    else if (stats.itemType == ItemType::Armor)
    {
        item = new Armor("Armor", stats.rarity, 0, stats.additionalDEF);
    }
    else if (stats.itemType == ItemType::Trinket)
    {
        item = new Trinket("Ammulet", stats.rarity, 0, stats.additionalHP);
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

#pragma once

#include <map>

struct Interval
{
    int min, max;
};

struct fInterval
{
    float min, max;
};

enum class ItemType
{
    Generic,
    Weapon,
    Armor,
    Trinket,
    Chest
};

enum class Rarities
{
    common,
    uncommon,
    rare,
    epic
};

enum class Statistic
{
    HP,
    DMG,
    DEF
};

struct GeneratedStats
{
    ItemType itemType;
    float additionalHP, additionalDMG, additionalDEF;
    Rarities rarity;
};

// std::map<ItemType, SDL_Texture *> ItemTextures;

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

enum class Rarities
{
    common,
    uncommon,
    rare,
    epic
};

enum class ItemType
{
    Weapon,
    Armor,
    Trinket
};

enum class ItemExactType
{
    Sword,
    Axe,
    Spear,
    Armor,
    Robe,

};

enum class Statistic
{
    HP,
    DMG,
    DEF
};

struct Preference
{
    Statistic preferedStat;
    Statistic hatedStat;
};

struct GeneratedStats
{
    ItemExactType itemType;
    float additionalHP, additionalDMG, additionalDEF;
};

const static std::map<ItemExactType, Preference> ItemStatPreferences = {
    {ItemExactType::Sword, {Statistic::DMG, Statistic::HP}},
    {ItemExactType::Axe, {Statistic::DMG, Statistic::HP}},
    {ItemExactType::Spear, {Statistic::DMG, Statistic::DEF}}};

std::map<ItemExactType, SDL_Texture *> ItemTextures;

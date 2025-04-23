#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>

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
    epic,
    legendary
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

struct EnemyStats
{
    float HP, DMG, DEF;
    int bHP, bDMG, bDEF;
};

// std::map<ItemType, SDL_Texture *> ItemTextures;

enum class PlayerPosition
{
    Lobby,
    Arena
};

enum class Direction
{
    Right,
    Left
};

extern std::map<int, int> moneyOnTier;
extern std::map<std::string, SDL_Texture *>
    loadedTextures;
extern std::map<int, EnemyStats> enemyTiers;
extern std::map<int, std::string> enemyNames;
extern std::map<int, std::string> enemyTexturesID;
#include <LootTable.hpp>

#include <time.h>
#include <map>
#include <iostream>

#include <Enums.hpp>

LootTable::LootTable()
{
}

GeneratedStats LootTable::generate()
{
    GeneratedStats stats;
    if (validItemsTypes.empty())
    {
        std::cout << "[LootTable.cpp/generate()] No valid types set.\n";

        return stats;
    }

    srand(time(NULL));

    ItemExactType type = ItemExactType::Sword;
    type = validItemsTypes[rand() % validItemsTypes.size()];
    stats.itemType = type;

    float HPmult = (float)(rand()) / (float)(RAND_MAX);
    float DMGmult = (float)(rand()) / (float)(RAND_MAX);
    float DEFmult = (float)(rand()) / (float)(RAND_MAX);

    std::map<Statistic, float> multipliers = {{Statistic::HP, HPmult}, {Statistic::DMG, DMGmult}, {Statistic::DEF, DEFmult}};

    Preference preference = ItemStatPreferences.find(type)->second;

    multipliers[preference.preferedStat] = multipliers[preference.preferedStat] * preferenceMultiplier;
    multipliers[preference.hatedStat] = multipliers[preference.hatedStat] / preferenceMultiplier;

    stats.additionalHP = statsIntervals[Statistic::HP].min + (HPmult * (statsIntervals[Statistic::HP].max - statsIntervals[Statistic::HP].min));
    stats.additionalDMG = statsIntervals[Statistic::DMG].min + (DMGmult * (statsIntervals[Statistic::DMG].max - statsIntervals[Statistic::DMG].min));
    stats.additionalDEF = statsIntervals[Statistic::DEF].min + (DEFmult * (statsIntervals[Statistic::DEF].max - statsIntervals[Statistic::DEF].min));

    return stats;
}

void LootTable::setHP(float min, float max)
{
    this->statsIntervals[Statistic::HP].min = min;
    this->statsIntervals[Statistic::HP].max = max;
}

void LootTable::setDMG(float min, float max)
{
    this->statsIntervals[Statistic::DMG].min = min;
    this->statsIntervals[Statistic::DMG].max = max;
}

void LootTable::setDEF(float min, float max)
{
    this->statsIntervals[Statistic::DEF].min = min;
    this->statsIntervals[Statistic::DEF].max = max;
}

void LootTable::setPreferenceMultiplier(float multiplier)
{
    this->preferenceMultiplier = multiplier;
}

void LootTable::setValidTypes(std::vector<ItemExactType> validItemsTypes)
{
    this->validItemsTypes = validItemsTypes;
}

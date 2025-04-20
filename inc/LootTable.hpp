#include <Enums.hpp>

#include <vector>
#include <map>
#include <SDL2/SDL.h>

class LootTable
{
private:
    float preferenceMultiplier = 1.3;

    std::map<Statistic, fInterval> statsIntervals = {{Statistic::HP, {0, 0}}, {Statistic::DMG, {0, 0}}, {Statistic::DEF, {0, 0}}};
    std::vector<ItemExactType> validItemsTypes;

public:
    LootTable();

    GeneratedStats generate();

    //? Setters

    void setHP(float min, float max);
    void setDMG(float min, float max);
    void setDEF(float min, float max);
    void setPreferenceMultiplier(float multiplier);
    void setValidTypes(std::vector<ItemExactType> validItemsTypes);
};

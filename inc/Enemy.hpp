#pragma once

#include <string>
#include <Enums.hpp>

class Enemy
{
private:
    std::string name;
    float HP, DMG, DEF;

    const float lvlRatio = 1.8;

    Interval HPinterval = {15, 30};
    Interval DMGinterval = {1, 5};
    Interval DEFinterval = {};

    void generateRandomStats();

public:
    Enemy();
    Enemy(std::string name);
    Enemy(std::string name, Interval HPinterval, Interval DMGinterval, Interval DEFinterval);
    Enemy(std::string name, float HP, float DMG, float DEF);

    //? Getters
    std::string getName();
};
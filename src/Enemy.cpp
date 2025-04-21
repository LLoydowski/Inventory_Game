#include "Enemy.hpp"
#include <time.h>
#include <string>

void Enemy::generateRandomStats()
{
    srand(time(NULL));

    float HPmult = (float)(rand()) / (float)(RAND_MAX);
    float DMGmult = (float)(rand()) / (float)(RAND_MAX);
    float DEFmult = (float)(rand()) / (float)(RAND_MAX);

    this->HP = HPinterval.min + (HPmult * (HPinterval.max - HPinterval.min));
    this->DMG = DMGinterval.min + (DMGmult * (DMGinterval.max - DMGinterval.min));
    this->DEF = DEFinterval.min + (DEFmult * (DEFinterval.max - DEFinterval.min));
}

Enemy::Enemy()
    : name{"Zombie"}
{
    this->HPinterval = {15, 30};
    this->DMGinterval = {1, 5};
    this->DEFinterval = {0, 2};
    generateRandomStats();
}

Enemy::Enemy(std::string name)
    : name{name}
{
    this->HPinterval = {15, 30};
    this->DMGinterval = {1, 5};
    this->DEFinterval = {0, 2};
    generateRandomStats();
}

Enemy::Enemy(std::string name, Interval HPinterval, Interval DMGinterval, Interval DEFinterval)
    : name{name}, HPinterval{HPinterval}, DMGinterval{DMGinterval}, DEFinterval{DEFinterval}
{
    generateRandomStats();
}

Enemy::Enemy(std::string name, float HP, float DMG, float DEF)
    : name{name}, HP{HP}, DMG{DMG}, DEF{DEF}
{
}

std::string Enemy::getName()
{
    return name;
}

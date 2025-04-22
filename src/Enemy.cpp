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
    this->tempHP = HP;
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
    : name{name}, HP{HP}, DMG{DMG}, DEF{DEF}, tempHP{HP}
{
}

void Enemy::display(SDL_Renderer *rend)
{
    int texWidth, texHeight;

    SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

    int displayX = posX - (texWidth / 2);
    int displayY = posY - (texHeight / 2);

    SDL_Rect dest = {displayX, displayY, texWidth, texHeight};
    SDL_RenderCopy(rend, texture, NULL, &dest);
}

void Enemy::dealDMG(float dmg)
{
    this->tempHP -= dmg;
}

void Enemy::setTexture(SDL_Texture *texture)
{
    this->texture = texture;
}

void Enemy::setPos(int x, int y)
{
    this->posX = x;
    this->posY = y;
}

std::string Enemy::getName()
{
    return name;
}

float Enemy::getHP()
{
    return HP;
}

float Enemy::getTempHP()
{
    return tempHP;
}

float Enemy::getDMG()
{
    return DMG;
}

float Enemy::getDEF()
{
    return DEF;
}

#pragma once

#include <string>
#include <Enums.hpp>
#include <SDL2/SDL.h>

class Enemy
{
private:
    std::string name;
    float HP, DMG, DEF;
    float tempHP;

    SDL_Texture *texture = nullptr;
    int posX, posY;

    Interval HPinterval = {15, 30};
    Interval DMGinterval = {1, 5};
    Interval DEFinterval = {};

    void generateRandomStats();

public:
    Enemy();
    Enemy(std::string name);
    Enemy(std::string name, Interval HPinterval, Interval DMGinterval, Interval DEFinterval);
    Enemy(std::string name, float HP, float DMG, float DEF);

    void display(SDL_Renderer *rend);

    //? Setters
    void setTexture(SDL_Texture *texture);
    void setPos(int x, int y);

    //? Getters
    std::string getName();
    float getHP();
    float getTempHP();
    float getDMG();
    float getDEF();
};
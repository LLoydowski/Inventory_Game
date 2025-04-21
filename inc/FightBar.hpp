#pragma once

#include <UIElement.hpp>
#include <Enums.hpp>

#include <SDL2/SDL.h>

class FightBar
{
private:
    int posX, posY, width, height;

    Direction crossDirection;
    int crossX;
    int crossSpeed = 5;
    int crossWidth = 5;

    int centerHitBox = 15;

    UIElement *background = nullptr;
    UIElement *crosshair = nullptr;
    UIElement *center = nullptr;

    void updateCrosshair();

public:
    FightBar(int posX, int posY, int width, int height);
    ~FightBar();

    void display(SDL_Renderer *rend);
    void hit();
    void setSpeed(int speed);
};
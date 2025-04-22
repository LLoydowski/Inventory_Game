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

    bool wasHit = false;

    int centerHitBox = 15;
    int mildHitBox = 150;

    UIElement *background = nullptr;
    UIElement *crosshair = nullptr;
    UIElement *center = nullptr;
    UIElement *mild = nullptr;

    const float CENTER_HIT = 1.5;
    const float MILD_HIT = 1;
    const float BAD_HIT = 0.7;

    void updateCrosshair();

public:
    FightBar(int posX, int posY, int width, int height);
    ~FightBar();

    void display(SDL_Renderer *rend);
    float hit();
    void setSpeed(int speed);
};
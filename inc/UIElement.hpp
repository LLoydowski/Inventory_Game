#pragma once

#include <SDL2/SDL.h>

#include <string>

class UIElement
{
protected:
    int width, height, posX, posY;
    std::string text;
    SDL_Color color, textColor;

public:
    UIElement();
    UIElement(int width, int height, int posX, int posY, SDL_Color color);
    UIElement(int width, int height, int posX, int posY, SDL_Color color, std::string text, SDL_Color textColor);

    void display(SDL_Renderer *rend);
};
#pragma once

#include <SDL2/SDL.h>
#include <UIELement.hpp>

class UIButton : public UIElement
{
private:
    SDL_Color hoverColor;

public:
    UIButton();
    UIButton(int width, int height, int posX, int posY, SDL_Color color);
    UIButton(int width, int height, int posX, int posY, SDL_Color color, std::string text, TTF_Font *font, SDL_Renderer *rend);
    void display(SDL_Renderer *rend) override;
    bool checkMouseCollision();
};
#pragma once

#include <SDL2/SDL.h>
#include <string>

#include <UIElement.hpp>

class UIImage : public UIElement
{
private:
    SDL_Texture *texture;

public:
    UIImage();
    UIImage(int width, int height, int posX, int posY, SDL_Texture *texture);
    void display(SDL_Renderer *rend) override;
};
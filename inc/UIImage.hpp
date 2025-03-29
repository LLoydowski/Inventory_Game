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
    UIImage(int width, int height, int posX, int posY, SDL_Texture *texture, SDL_Color color);
    void display(SDL_Renderer *rend) override;
    void display(SDL_Renderer *rend, int padding);
    void setTexture(SDL_Texture *texture);
};
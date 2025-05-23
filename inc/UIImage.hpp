#pragma once

#include <SDL2/SDL.h>
#include <string>

#include <UIElement.hpp>

class UIImage : public virtual UIElement
{
protected:
    SDL_Texture *texture;

public:
    UIImage();
    UIImage(int width, int height, int posX, int posY, SDL_Texture *texture);
    UIImage(int width, int height, int posX, int posY, SDL_Texture *texture, SDL_Color color);
    ~UIImage();
    void display(SDL_Renderer *rend) override;
    virtual void display(SDL_Renderer *rend, int padding);
    void setTexture(SDL_Texture *texture);
};
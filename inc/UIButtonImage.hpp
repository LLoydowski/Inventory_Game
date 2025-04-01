#pragma once

#include <SDL2/SDL.h>

#include "UIButton.hpp"
#include "UIImage.hpp"

class UIButtonImage : public UIButton, public UIImage
{
public:
    UIButtonImage();
    UIButtonImage(int width, int height, int posX, int posY, SDL_Texture *texture);
    UIButtonImage(int width, int height, int posX, int posY, SDL_Texture *texture, SDL_Color color);

    void display(SDL_Renderer *rend) override;
};
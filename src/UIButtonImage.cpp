#include "UIButtonImage.hpp"
#include "UIImage.hpp"
#include "UIButton.hpp"

#include <iostream>

UIButtonImage::UIButtonImage()
    : UIImage()
{
}
UIButtonImage::UIButtonImage(int width, int height, int posX, int posY, SDL_Texture *texture)
    : UIImage(width, height, posX, posY, texture)
{
    this->width = width;
    this->height = height;
    this->posX = posX;
    this->posY = posY;
    this->texture = texture;
}
UIButtonImage::UIButtonImage(int width, int height, int posX, int posY, SDL_Texture *texture, SDL_Color color)
    : UIImage(width, height, posX, posY, texture, color)
{
    //! I have no fucking idea why this constructor doesnt call, I mean it kinda does but doesnt assign the values.
    this->width = width;
    this->height = height;
    this->posX = posX;
    this->posY = posY;
    this->texture = texture;
    this->color = color;
}

void UIButtonImage::display(SDL_Renderer *rend)
{
    SDL_Rect dest = {posX, posY, width, height};
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &dest);
    SDL_RenderCopy(rend, texture, NULL, &dest);
}

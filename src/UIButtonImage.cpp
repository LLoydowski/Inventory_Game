#include "UIButtonImage.hpp"
#include "UIImage.hpp"
#include "UIButton.hpp"

#include <iostream>

UIButtonImage::UIButtonImage()
    : UIImage()
{
}
UIButtonImage::UIButtonImage(int width, int height, int posX, int posY, SDL_Texture *texture)
    : UIElement(width, height, posX, posY), UIImage(width, height, posX, posY, texture)
{
}
UIButtonImage::UIButtonImage(int width, int height, int posX, int posY, SDL_Texture *texture, SDL_Color color)
    : UIElement(width, height, posX, posY), UIImage(width, height, posX, posY, texture, color)
{
    this->color = color;
    text = "";
    textTexture = nullptr;
}

UIButtonImage::~UIButtonImage()
{
    if (textTexture != nullptr && textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
    if (texture != nullptr && texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void UIButtonImage::display(SDL_Renderer *rend)
{
    SDL_Rect dest = {posX, posY, width, height};
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &dest);
    SDL_RenderCopy(rend, texture, NULL, &dest);
}

void UIButtonImage::display(SDL_Renderer *rend, int padding)
{
    SDL_Rect dest = {posX, posY, width, height};
    SDL_Rect itemDest = {posX + padding / 2, posY + padding / 2, width - padding, height - padding};
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &dest);
    SDL_RenderCopy(rend, texture, NULL, &itemDest);
}

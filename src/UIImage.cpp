#include <SDL2/SDL.h>

#include <UIImage.hpp>

UIImage::UIImage() : UIElement()
{
    color = {255, 255, 255, 255};
}

UIImage::UIImage(int width, int height, int posX, int posY, SDL_Texture *texture)
    : UIElement(width, height, posX, posY), texture{texture}
{
    color = {255, 255, 255, 255};
}
UIImage::UIImage(int width, int height, int posX, int posY, SDL_Texture *texture, SDL_Color color)
    : UIElement(width, height, posX, posY, color), texture{texture}
{
}

UIImage::~UIImage()
{
    if (texture != nullptr && texture != NULL)
    {
        SDL_DestroyTexture(texture);
    }
}

void UIImage::display(SDL_Renderer *rend)
{

    SDL_Rect dest = {posX, posY, width, height};
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &dest);
    SDL_RenderCopy(rend, texture, NULL, &dest);
}

void UIImage::display(SDL_Renderer *rend, int padding)
{
    SDL_Rect dest = {posX, posY, width, height};
    SDL_Rect itemDest = {posX + padding / 2, posY + padding / 2, width - padding, height - padding};
    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &dest);
    SDL_RenderCopy(rend, texture, NULL, &itemDest);
}

void UIImage::setTexture(SDL_Texture *texture)
{
    this->texture = texture;
}

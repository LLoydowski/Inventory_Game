#include <SDL2/SDL.h>

#include <UIImage.hpp>

UIImage::UIImage() : UIElement()
{
    color = {255, 255, 255, 255};
}

UIImage::UIImage(int width, int height, int posX, int posY, SDL_Texture *texture)
    : UIElement(width, height, posX, posY), texture{texture}
{
}

void UIImage::display(SDL_Renderer *rend)
{
    SDL_Rect dest = {posX, posY, width, height};
    SDL_RenderCopy(rend, texture, NULL, &dest);
}

#include <string>
#include <SDL2/SDL.h>

#include <UIElement.hpp>

UIElement::UIElement() : width{250}, height{100}, posX{0}, posY{0}, text{"Test button"}
{
    color = {255, 255, 255, 255};
    textColor = {0, 0, 0, 255};
}

UIElement::UIElement(int width, int height, int posX, int posY, SDL_Color color)
    : width{width}, height{height}, posX{posX}, posY{posY}, color{color}, text{""}
{
    textColor = {0, 0, 0, 255};
}

UIElement::UIElement(int width, int height, int posX, int posY, SDL_Color color, std::string text, SDL_Color textColor)
    : width{width}, height{height}, posX{posX}, posY{posY}, text{text}, textColor{textColor}
{
}

void UIElement::display(SDL_Renderer *rend)
{
    SDL_Rect rect = {posX, posY, width, height};

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &rect);
}
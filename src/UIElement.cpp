#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include <UIElement.hpp>

UIElement::UIElement() : width{250}, height{100}, posX{0}, posY{0}, text{"Test button"}
{
    color = {255, 255, 255, 255};
}

UIElement::UIElement(int width, int height, int posX, int posY, SDL_Color color)
    : width{width}, height{height}, posX{posX}, posY{posY}, color{color}, text{""}
{
}

UIElement::~UIElement()
{
}

void UIElement::display(SDL_Renderer *rend)
{
    SDL_Rect rect = {posX, posY, width, height};

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &rect);

    if (text != "")
    {
    }
}

int UIElement::getWidth()
{
    return width;
}

int UIElement::getHeight()
{
    return height;
}

int UIElement::getX()
{
    return posX;
}

int UIElement::getY()
{
    return posY;
}

void UIElement::setText(std::string text)
{
    this->text = text;
}

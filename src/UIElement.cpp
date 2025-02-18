#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include <UIElement.hpp>

UIElement::UIElement() : width{250}, height{100}, posX{0}, posY{0}, text{"Test button"}, textTexture{nullptr}
{
    color = {255, 255, 255, 255};
}

UIElement::UIElement(int width, int height, int posX, int posY, SDL_Color color)
    : width{width}, height{height}, posX{posX}, posY{posY}, color{color}, text{""}, textTexture{nullptr}
{
}

UIElement::~UIElement()
{
    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
    }
}

void UIElement::display(SDL_Renderer *rend)
{
    SDL_Rect rect = {posX, posY, width, height};

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(rend, &rect);

    if (text != "")
    {
        int texWidth, texHeight;
        SDL_QueryTexture(textTexture, NULL, NULL, &texWidth, &texHeight);

        SDL_Rect textRect = {0, 0, texWidth, texHeight};

        SDL_RenderCopy(rend, textTexture, &textRect, &rect);
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

std::string UIElement::getText()
{
    return text;
}

void UIElement::setText(std::string text)
{
    this->text = text;
}

void UIElement::setText(std::string text, TTF_Font *font, SDL_Renderer *rend)
{
    this->text = text;
    SDL_Color color = {0, 0, 0};

    if (font == nullptr)
    {
        std::cout << "Font is nullptr. Cannot render text." << std::endl;
        return;
    }

    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr)
    {
        std::cout << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return;
    }

    textTexture = SDL_CreateTextureFromSurface(rend, surface);
    if (textTexture == nullptr)
    {
        std::cout << "Failed to create text texture: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
}

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include <UIElement.hpp>

UIElement::UIElement() : width{250}, height{100}, posX{0}, posY{0}, text{"Test button"}, textTexture{nullptr}
{
    color = {255, 255, 255, 255};
}
UIElement::UIElement(int width, int height, int posX, int posY)
    : width{width}, height{height}, posX{posX}, posY{posY}
{
    color = {255, 255, 255, 255};
}
UIElement::UIElement(int width, int height, int posX, int posY, SDL_Color color)
    : width{width}, height{height}, posX{posX}, posY{posY}, color{color}, text{""}, textTexture{nullptr}
{
}
UIElement::UIElement(int width, int height, int posX, int posY, SDL_Color color, std::string text, TTF_Font *font, SDL_Renderer *rend)
    : width{width}, height{height}, posX{posX}, posY{posY}, color{color}, text{text}, textTexture{nullptr}
{
    generateTexture(font, rend);
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

        SDL_Rect paddedRect = {posX + textPadding, posY + textPadding, width - 2 * textPadding, height - 2 * textPadding};

        SDL_RenderCopy(rend, textTexture, &textRect, &paddedRect);
    }
}
bool UIElement::generateTexture(TTF_Font *font, SDL_Renderer *rend)
{
    SDL_Color color = {0, 0, 0, 0};

    if (text == "")
    {
        std::cout << "Text cnnot be empty" << std::endl;
        return false;
    }

    if (font == nullptr)
    {
        std::cout << "Font is nullptr. Cannot render text." << std::endl;
        return false;
    }

    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
    if (surface == nullptr)
    {
        std::cout << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return false;
    }

    textTexture = SDL_CreateTextureFromSurface(rend, surface);
    if (textTexture == nullptr)
    {
        std::cout << "Failed to create text texture: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
    return true;
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
    generateTexture(font, rend);
}

void UIElement::setTextPadding(int textPadding)
{
    this->textPadding = textPadding;
}

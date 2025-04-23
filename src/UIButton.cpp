#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <iostream>

#include <UIButton.hpp>

UIButton::UIButton() : UIElement()
{
    int r, g, b;
    r = color.r - 25;
    g = color.g - 25;
    b = color.b - 25;

    if (r < 0)
    {
        r = 0;
    }
    if (g < 0)
    {
        g = 0;
    }
    if (b < 0)
    {
        b = 0;
    }

    hoverColor.a = 255;
    hoverColor.r = r;
    hoverColor.g = g;
    hoverColor.b = b;
}
UIButton::UIButton(int width, int height, int posX, int posY, SDL_Color color)
    : UIElement(width, height, posX, posY, color)
{

    int r, g, b;
    r = color.r - 25;
    g = color.g - 25;
    b = color.b - 25;

    if (r < 0)
    {
        r = 0;
    }
    if (g < 0)
    {
        g = 0;
    }
    if (b < 0)
    {
        b = 0;
    }

    hoverColor.a = 255;
    hoverColor.r = r;
    hoverColor.g = g;
    hoverColor.b = b;
}
UIButton::UIButton(int width, int height, int posX, int posY, SDL_Color color, std::string text, TTF_Font *font, SDL_Renderer *rend)
    : UIElement(width, height, posX, posY, color, text, font, rend)
{

    int r, g, b;
    r = color.r - 25;
    g = color.g - 25;
    b = color.b - 25;

    if (r < 0)
    {
        r = 0;
    }
    if (g < 0)
    {
        g = 0;
    }
    if (b < 0)
    {
        b = 0;
    }

    hoverColor.a = 255;
    hoverColor.r = r;
    hoverColor.g = g;
    hoverColor.b = b;
}

UIButton::~UIButton()
{

    if (textTexture != nullptr)
    {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }
}

void UIButton::display(SDL_Renderer *rend)
{
    int realX = posX;
    int realY = posY;
    if (hasParent)
    {
        realX += parentX;
        realY += parentY;
    }

    SDL_Rect rect = {realX, realY, width, height};

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    if (checkMouseCollision())
    {
        SDL_SetRenderDrawColor(rend, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
    }
    SDL_RenderFillRect(rend, &rect);

    if (text != "")
    {
        int texWidth, texHeight;
        SDL_QueryTexture(textTexture, NULL, NULL, &texWidth, &texHeight);

        float scaleRatio = float(this->height) / float(texHeight);

        SDL_Rect textRect = {0, 0, texWidth, texHeight};

        SDL_Rect paddedRect = {realX + textPadding, realY + textPadding, int(texWidth * scaleRatio), int(texHeight * scaleRatio)};

        SDL_RenderCopy(rend, textTexture, &textRect, &paddedRect);
    }
}

void UIButton::callAction()
{
    action();
}

bool UIButton::checkMouseCollision()
{
    if (enabled)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        int realX = posX;
        int realY = posY;

        if (hasParent)
        {
            realX += parentX;
            realY += parentY;
        }

        if ((mouseX >= realX && mouseX <= realX + width) && (mouseY >= realY && mouseY <= realY + height))
        {
            // std::cout << "[UIButton/checkMouseCollision] MouseX: " << mouseX << " MouseY: " << mouseY;
            // std::cout << " PosX: " << posX << " PosY: " << posY;
            // std::cout << " Width: " << width << " Height: " << height << std::endl;
            return true;
        }
    }
    return false;
}

void UIButton::setAction(std::function<void()> action)
{
    this->action = action;
}

void UIButton::enable()
{
    enabled = true;
}

void UIButton::disable()
{
    enabled = false;
}

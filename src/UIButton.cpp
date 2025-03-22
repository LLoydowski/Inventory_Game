#include <UIButton.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

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

void UIButton::display(SDL_Renderer *rend)
{
    SDL_Rect rect = {posX, posY, width, height};

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

        SDL_Rect paddedRect = {posX + textPadding, posY + textPadding, width - 2 * textPadding, height - 2 * textPadding};
        SDL_Rect textRect = {0, 0, texWidth, texHeight};

        SDL_RenderCopy(rend, textTexture, &textRect, &paddedRect);
    }
}

bool UIButton::checkMouseCollision()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if ((mouseX >= posX && mouseX <= posX + width) && (mouseY >= posY && mouseY <= posY + height))
    {

        return true;
    }

    return false;
}

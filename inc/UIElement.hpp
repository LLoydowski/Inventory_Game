#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class UIElement
{
protected:
    int width, height, posX, posY;
    std::string text;
    SDL_Color color;
    SDL_Texture *textTexture;

    int textPadding = 5;

public:
    UIElement();
    UIElement(int width, int height, int posX, int posY, SDL_Color color);
    UIElement(int width, int height, int posX, int posY, SDL_Color color, std::string text, TTF_Font *font, SDL_Renderer *rend);
    ~UIElement();

    virtual void display(SDL_Renderer *rend);
    bool generateTexture(TTF_Font *font, SDL_Renderer *rend);

    int getWidth();
    int getHeight();
    int getX();
    int getY();
    std::string getText();

    void setText(std::string text);
    void setText(std::string text, TTF_Font *font, SDL_Renderer *rend);
    void setTextPadding(int textPadding);
};
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <map>

class UIElement
{
protected:
    int width, height, posX, posY;
    SDL_Color color;
    std::string text;
    SDL_Texture *textTexture;

    int textPadding = 1.5;

    bool hasParent = false;
    int parentX, parentY;

public:
    std::map<std::string, int> params;

    UIElement();
    UIElement(int width, int height, int posX, int posY);
    UIElement(int width, int height, int posX, int posY, SDL_Color color);
    UIElement(int width, int height, int posX, int posY, SDL_Color color, std::string text, TTF_Font *font, SDL_Renderer *rend);
    virtual ~UIElement();

    virtual void display(SDL_Renderer *rend);
    bool generateTexture(TTF_Font *font, SDL_Renderer *rend);

    int getWidth();
    int getHeight();
    int getX();
    int getY();
    std::string getText();
    SDL_Texture *getTextTexture();

    void setText(std::string text);
    void setText(std::string text, TTF_Font *font, SDL_Renderer *rend);
    void setTextPadding(int textPadding);
    void setParentPos(int posX, int posY);
    void setSize(int width, int height);
    void setX(int x);
};
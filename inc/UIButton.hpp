#pragma once

#include <SDL2/SDL.h>
#include <UIELement.hpp>
#include <functional>

class UIButton : public virtual UIElement
{
protected:
    SDL_Color hoverColor;
    std::function<void()> action;

    bool enabled = true;

public:
    UIButton();
    UIButton(int width, int height, int posX, int posY, SDL_Color color);
    UIButton(int width, int height, int posX, int posY, SDL_Color color, std::string text, TTF_Font *font, SDL_Renderer *rend);
    ~UIButton();
    void display(SDL_Renderer *rend) override;
    void callAction();
    bool checkMouseCollision();
    void setAction(std::function<void()> action);

    void enable();
    void disable();
};
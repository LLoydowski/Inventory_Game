#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <typeinfo>

#include <Inventory.hpp>
#include <Shop.hpp>
#include <Item.hpp>
#include <UIElement.hpp>
#include <UIButton.hpp>
#include <UIImage.hpp>
#include <Player.hpp>
#include <UIButtonImage.hpp>
#include <Weapon.hpp>
#include <Chest.hpp>
#include <Arena.hpp>
#include <FightBar.hpp>

class Game
{
private:
    int windowWidth = 800;
    int windowHeight = 500;

    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;

public:
    Game();
};
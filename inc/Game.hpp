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

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    TTF_Font *font = nullptr;

    Player *player = nullptr;
    Shop *shop = nullptr;
    Arena *arena = nullptr;
    UIButton *goToArenaButton = nullptr;
    UIElement *tierDisplay = nullptr;

    bool InitializeSDL(int windowWidth, int windowHeight, SDL_Window *&window, SDL_Renderer *&renderer, TTF_Font *&font);
    void LoadTextures(SDL_Renderer *rend);
    void RemoveTextures();
    Shop *CreateShop(SDL_Renderer *rend, Player *plr);
    void HandleLobbyLogic(SDL_Event &e, Inventory *playerInv, Shop *shop, UIButton *goArenaBtn);
    void HandleArenaLogic(SDL_Event &e, Arena *arena);

public:
    ~Game();
    Game(int windowWidth, int windowHeight);

    void Init();
    void HandleEvents(SDL_Event event);
    void Draw();
    void CleanUp();
};
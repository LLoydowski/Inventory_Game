#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <typeinfo>

#include <Game.hpp>

std::map<std::string, SDL_Texture *> loadedTextures;
std::map<int, int> moneyOnTier = {
    {1, 10},
    {2, 45},
    {3, 85},
    {4, 175},
    {5, 425}};
std::map<int, EnemyStats> enemyTiers = {
    {1, {15, 10, 0, 10, 5, 3}},
    {2, {35, 25, 5, 10, 5, 4}},
    {3, {70, 30, 10, 12, 5, 5}},
    {4, {100, 40, 15, 15, 5, 5}},
    {5, {150, 40, 30, 15, 10, 5}}};

int main(int argc, char *argv[])
{
    (void)argc; // Mark argc as unused
    (void)argv; // Mark argv as unused

    const int FPS = 144;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    //? Declaring window size
    int windowWidth = 800;
    int windowHeight = 500;

    Game *game = new Game(windowWidth, windowHeight);

    bool isRunning = true;
    SDL_Event e;

    while (isRunning)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
            }
            game->HandleEvents(e);
        }

        game->Draw();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    delete game;

    return 0;
}
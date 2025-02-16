#include <SDL2/SDL.h>
#include <iostream>

#include <Inventory.hpp>
#include <Item.hpp>
#include <UIElement.hpp>
#include <UIButton.hpp>

int main(int argc, char *argv[])
{
    int windowWidth = 800;
    int windowHeight = 500;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Inventory Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event e;

    Inventory inv(2, 6, windowWidth, windowHeight);
    inv.displayCLI();

    std::cout << std::endl;

    Item *item = new Item("Armor", common, 30);
    inv.addItem(item);
    inv.displayCLI();

    bool isRunning = true;

    //? Game loop
    while (isRunning)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 74, 94, 224, SDL_ALPHA_OPAQUE); //? Sets background color
        SDL_RenderClear(renderer);

        inv.displaySDL(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
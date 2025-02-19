#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include <Inventory.hpp>
#include <Item.hpp>
#include <UIElement.hpp>
#include <UIButton.hpp>
#include <Player.hpp>

int main(int argc, char *argv[])
{
    int windowWidth = 800;
    int windowHeight = 500;

    //? SDL2 initialization
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Inventory Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //? SDL2_TTF initialization
    TTF_Init();

    // Player *player = new Player("Jasiu", 100.0, 20.0);

    Inventory *inv = new Inventory(3, 4);
    inv->setWindowParams(windowWidth, windowHeight, renderer);
    inv->generateUIElements();
    Item *item = new Item("Skibidi", rare, 100);
    inv->addItem(item);
    inv->displayCLI();

    SDL_Color btnColor = {189, 189, 189};

    TTF_Font *font = TTF_OpenFont("font/OpenSans.ttf", 72);
    UIButton btn(200, 100, 100, 100, btnColor, "Wybierz gracza", font, renderer);
    UIButton btn2(200, 100, 100, 225, btnColor, "Pokaż graczy", font, renderer);
    TTF_CloseFont(font);

    //? Game loop
    bool isRunning = true;
    SDL_Event e;

    while (isRunning)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
                break;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (btn.checkMouseCollision())
                {
                    std::cout << "Button 1 pressed" << std::endl;
                }
                else if (btn2.checkMouseCollision())
                {
                    std::cout << "Button 2 pressed" << std::endl;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 74, 94, 224, SDL_ALPHA_OPAQUE); //? Sets background color
        SDL_RenderClear(renderer);

        btn.display(renderer);
        btn2.display(renderer);
        inv->displaySDL(renderer);

        SDL_RenderPresent(renderer);
    }

    delete inv;

    TTF_Quit();
    SDL_Quit();
    return 0;
}
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include <Inventory.hpp>
#include <Shop.hpp>
#include <Item.hpp>
#include <UIElement.hpp>
#include <UIButton.hpp>
#include <UIImage.hpp>
#include <Player.hpp>
#include <UIButtonImage.hpp>

void doSth() //! To be removed
{
    std::cout << "Skibadi Action to a butotn" << std::endl;
}

int main(int argc, char *argv[])
{
    (void)argc; // Mark argc as unused
    (void)argv; // Mark argv as unused
    int windowWidth = 800;
    int windowHeight = 500;

    //? SDL2 initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Inventory Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //? SDL2_TTF initialization
    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("font/OpenSans.ttf", 72);
    if (font == nullptr)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    //? Loading textures

    SDL_Texture *placeholderTexture = NULL;
    SDL_Surface *testSurface = IMG_Load("gfx/placeholder.png");
    if (testSurface)
    {
        placeholderTexture = SDL_CreateTextureFromSurface(renderer, testSurface);
        SDL_FreeSurface(testSurface);
    }

    SDL_Texture *sword01Texture = NULL;
    SDL_Surface *sword01Surf = IMG_Load("gfx/Sword01.png");
    if (sword01Surf)
    {
        sword01Texture = SDL_CreateTextureFromSurface(renderer, sword01Surf);
        SDL_FreeSurface(sword01Surf);
    }

    //? Game Logic

    // Player *player = new Player("Jasiu", 100.0, 20.0);

    std::vector<UIButton *> buttons;

    Inventory *inv = new Inventory(6, 3);
    inv->setPosAndUIParent(10, 10, renderer, &buttons);
    Item *item = new Item("Skibidi", rare, 100, sword01Texture);
    inv->addItem(item);
    Item *item2 = new Item("Skibidi2", rare, 100, sword01Texture);
    inv->addItem(item2);
    Item *item3 = new Item("Skibidi3", rare, 100, sword01Texture);
    inv->addItem(item3);

    // Shop *shop = new Shop(2, 2);
    // shop->setPos(500, 0, renderer);

    //? UI ELEMENTS
    std::vector<UIElement *> UI;

    // SDL_Color btnColor = {189, 189, 189, 255};

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
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                for (UIButton *button : buttons)
                {
                    if (button->checkMouseCollision())
                    {
                        button->callAction();
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 74, 94, 224, SDL_ALPHA_OPAQUE); //? Sets background color
        SDL_RenderClear(renderer);

        // TODO FIX Disabled buttons

        inv->displaySDL(renderer);
        // shop->displaySDL(renderer);

        // for (UIElement *element : UI)
        // {
        //     element->display(renderer);
        // }

        SDL_RenderPresent(renderer);
    }

    delete inv;
    // delete shop;

    for (int i = 0; i < int(buttons.size()); i++)
    {
        delete buttons[i];
    }
    buttons.clear();

    TTF_CloseFont(font);

    SDL_DestroyTexture(placeholderTexture);
    SDL_DestroyTexture(sword01Texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
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

std::map<std::string, SDL_Texture *> loadedTextures;

bool InitializeSDL(int windowWidth, int windowHeight, SDL_Window *&window, SDL_Renderer *&renderer)
{
    //? SDL2 initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Inventory Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    //? SDL2_TTF initialization
    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void LoadTextures(SDL_Renderer *rend)
{
    SDL_Texture *placeholderTexture = NULL;
    SDL_Surface *testSurface = IMG_Load("gfx/placeholder.png");
    if (testSurface)
    {
        placeholderTexture = SDL_CreateTextureFromSurface(rend, testSurface);
        SDL_FreeSurface(testSurface);
    }
    loadedTextures["placeholder"] = placeholderTexture;

    SDL_Texture *sword01Texture = NULL;
    SDL_Surface *sword01Surf = IMG_Load("gfx/Sword01.png");
    if (sword01Surf)
    {
        sword01Texture = SDL_CreateTextureFromSurface(rend, sword01Surf);
        SDL_FreeSurface(sword01Surf);
    }
    loadedTextures["Sword01"] = sword01Texture;

    SDL_Texture *weaponChestT1Texture = NULL;
    SDL_Surface *weaponChestT1Surf = IMG_Load("gfx/chest.png");
    if (weaponChestT1Surf)
    {
        weaponChestT1Texture = SDL_CreateTextureFromSurface(rend, weaponChestT1Surf);
        SDL_FreeSurface(weaponChestT1Surf);
    }
    loadedTextures["WeaponChest01"] = weaponChestT1Texture;
}

void RemoveTextures()
{
    for (const auto &[name, texture] : loadedTextures)
    {
        if (texture != nullptr)
        {
            std::cout << "[Main/RemoveTextures] Removing texture: " << name << "\n";
            SDL_DestroyTexture(texture);
            loadedTextures[name] = nullptr;
        }
    }
}

Shop *CreateShop(SDL_Renderer *rend, Player *plr)
{
    Shop *shop = new Shop(2, 2);
    shop->setPos(500, 0, rend);
    shop->setPlayerUsingShop(plr);

    //? Creating loot table for T1 Weapon Chest
    LootTable *weaponT1Loot = new LootTable();
    weaponT1Loot->setDMG(1, 10);
    weaponT1Loot->addValidType(ItemType::Weapon);

    //? Creating chest object
    Chest *chestWeapon1 = new Chest("Weapon Chest [T1]", Rarities::common, 10, loadedTextures["WeaponChest01"], weaponT1Loot);
    shop->addItem(chestWeapon1);

    return shop;
}

//? Handles lobby (not arena) logic
void HandleLobbyLogic(SDL_Event &e, Inventory *playerInv, Shop *shop)
{

    if (e.type == SDL_MOUSEBUTTONDOWN)
    {

        bool wasActionCalled = false;
        if (!wasActionCalled)
        {
            if (playerInv->handleClickEvents())
            {
                wasActionCalled = true;

                //? Clearing shop menu
                shop->removeMenu();
                shop->disableMoveMode();
            }
        }
        if (!wasActionCalled)
        {
            if (shop->handleClickEvents())
            {
                wasActionCalled = true;
                //? Clearing inventory menu
                playerInv->removeMenu();
                playerInv->disableMoveMode();
            }
        }
    }
}

int main(int argc, char *argv[])
{
    (void)argc; // Mark argc as unused
    (void)argv; // Mark argv as unused

    //? Declaring window size
    int windowWidth = 800;
    int windowHeight = 500;

    //? Initializing SDL2, SDL_TTF and SDL_image
    SDL_Window *window;
    SDL_Renderer *renderer;
    InitializeSDL(windowWidth, windowHeight, window, renderer);

    LoadTextures(renderer);

    //? Game Logic

    Player *player = new Player("Player", 100.0, 100.0);

    Inventory *playerInv = player->getInv();
    playerInv->setPos(10, 10, renderer);

    //* DEBUGING PURPOSES ONLY
    Item *item = new Item("DlugiSkibidi", Rarities::rare, 100, loadedTextures["placeholder"]);
    playerInv->addItem(item);
    Item *item2 = new Weapon("Skibidi2", Rarities::rare, 100, loadedTextures["Sword01"], 1);
    playerInv->addItem(item2);
    //* ----------------------

    Shop *shop = CreateShop(renderer, player);

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

            if (player->getPlayerPosition() == PlayerPosition::Lobby)
            {
                HandleLobbyLogic(e, playerInv, shop);
            }
            else
            {
            }
        }

        SDL_SetRenderDrawColor(renderer, 74, 94, 224, SDL_ALPHA_OPAQUE); //? Sets background color
        SDL_RenderClear(renderer);

        if (player->getPlayerPosition() == PlayerPosition::Lobby)
        {
            playerInv->displaySDL(renderer);
            shop->displaySDL(renderer);
        }
        else
        {
        }

        SDL_RenderPresent(renderer);
    }

    delete player;
    delete shop;

    RemoveTextures();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
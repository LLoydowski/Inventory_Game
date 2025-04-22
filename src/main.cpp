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

std::map<std::string, SDL_Texture *> loadedTextures;
std::map<int, EnemyStats> enemyTiers = {
    {1, {15, 10, 0, 10, 5, 3}},
    {2, {35, 25, 5, 10, 5, 4}},
    {3, {70, 30, 10, 12, 5, 5}},
    {4, {100, 40, 15, 15, 5, 5}},
    {5, {150, 40, 30, 15, 10, 5}}};

bool InitializeSDL(int windowWidth, int windowHeight, SDL_Window *&window, SDL_Renderer *&renderer, TTF_Font *&font)
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

    font = TTF_OpenFont("font/OpenSans.ttf", 54);
    if (font == nullptr)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
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
    Shop *shop = new Shop(2, 3);
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
void HandleLobbyLogic(SDL_Event &e, Inventory *playerInv, Shop *shop, UIButton *goArenaBtn)
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
        if (!wasActionCalled)
        {
            if (goArenaBtn->checkMouseCollision())
            {
                wasActionCalled = true;
                goArenaBtn->callAction();
            }
        }
    }
}

void HandleArenaLogic(SDL_Event &e, UIButton *goBackButton, Arena *arena)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        bool wasActionCalled = false;
        if (!wasActionCalled)
        {
            if (goBackButton->checkMouseCollision())
            {
                wasActionCalled = true;
                goBackButton->callAction();
            }
        }
        if (!wasActionCalled)
        {
            if (arena->handleClickEvents())
            {
                wasActionCalled = true;
            }
        }
    }
}

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

    //? Initializing SDL2, SDL_TTF and SDL_image
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    InitializeSDL(windowWidth, windowHeight, window, renderer, font);

    LoadTextures(renderer);

    //? Lobby Items

    Player *player = new Player("Player", 100.0, 100.0);

    Inventory *playerInv = player->getInv();
    playerInv->setPos(10, 10, renderer);

    //* DEBUGING PURPOSES ONLY
    Item *item = new Item("DlugiSkibidi", Rarities::rare, 100, loadedTextures["placeholder"]);
    playerInv->addItem(item);
    Item *item2 = new Weapon("Skibidi2", Rarities::rare, 100, loadedTextures["Sword01"], 100000);
    playerInv->addItem(item2);
    //* ----------------------

    Shop *shop = CreateShop(renderer, player);

    //? Arena stuff

    Arena *arena = new Arena(player);
    arena->calibrateWindowPos(windowWidth, windowHeight, renderer, font);

    UIButton *goToArenaButton = new UIButton(200, 50, 50, 400, {255, 0, 0, 1}, "Go to Arena", font, renderer);
    goToArenaButton->setAction(
        [player, arena]()
        {
            if (player->getInv()->getWeapon() != nullptr)
            {
                player->goToArena();
                arena->nextFight();
            }
        });

    //* DEBUG BUTTON
    UIButton *goBackButton = new UIButton(200, 50, windowWidth / 2 - 100, 10, {0, 255, 0, 1}, "/Go Back/", font, renderer);
    goBackButton->setAction([player]()
                            { player->goToLobby(); });

    //? Game loop
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

            if (e.type == SDL_KEYDOWN)
            {
                if (player->getPlayerPosition() == PlayerPosition::Arena)
                {
                    arena->handleKeyboardEvents(e);
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (player->getPlayerPosition() == PlayerPosition::Lobby)
                {
                    HandleLobbyLogic(e, playerInv, shop, goToArenaButton);
                }
                else
                {
                    HandleArenaLogic(e, goBackButton, arena);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 74, 94, 224, SDL_ALPHA_OPAQUE); //? Sets background color
        SDL_RenderClear(renderer);

        if (player->getPlayerPosition() == PlayerPosition::Lobby)
        {
            playerInv->displaySDL(renderer);
            shop->displaySDL(renderer);
            goToArenaButton->display(renderer);
        }
        else
        {
            goBackButton->display(renderer);
            arena->display();
        }

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    delete player;
    delete shop;
    delete goToArenaButton;
    delete arena;

    RemoveTextures();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
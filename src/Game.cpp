#include <SDL2/SDL.h>

#include <Game.hpp>

bool Game::InitializeSDL(int windowWidth, int windowHeight, SDL_Window *&window, SDL_Renderer *&renderer, TTF_Font *&font)
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

    LoadTextures(renderer);

    return true;
}

void Game::LoadTextures(SDL_Renderer *rend)
{
    SDL_Texture *placeholderTexture = NULL;
    SDL_Surface *testSurface = IMG_Load("gfx/placeholder.png");
    if (testSurface)
    {
        placeholderTexture = SDL_CreateTextureFromSurface(rend, testSurface);
        SDL_FreeSurface(testSurface);
    }
    loadedTextures["placeholder"] = placeholderTexture;

    SDL_Texture *weaponChestT1Texture = NULL;
    SDL_Surface *weaponChestT1Surf = IMG_Load("gfx/chest.png");
    if (weaponChestT1Surf)
    {
        weaponChestT1Texture = SDL_CreateTextureFromSurface(rend, weaponChestT1Surf);
        SDL_FreeSurface(weaponChestT1Surf);
    }
    loadedTextures["WeaponChest01"] = weaponChestT1Texture;

    //* T1 Items (No chests)

    SDL_Texture *sword01Texture = NULL;
    SDL_Surface *sword01Surf = IMG_Load("gfx/sword/Sword01.png");
    if (sword01Surf)
    {
        sword01Texture = SDL_CreateTextureFromSurface(rend, sword01Surf);
        SDL_FreeSurface(sword01Surf);
    }
    loadedTextures["Sword01"] = sword01Texture;

    SDL_Texture *armor01Texture = NULL;
    SDL_Surface *armor01Surf = IMG_Load("gfx/armor/Armor01.png");
    if (armor01Surf)
    {
        armor01Texture = SDL_CreateTextureFromSurface(rend, armor01Surf);
        SDL_FreeSurface(armor01Surf);
    }
    loadedTextures["Armor01"] = armor01Texture;

    SDL_Texture *trinket01Texture = NULL;
    SDL_Surface *trinket01Surf = IMG_Load("gfx/trinket/Trinket01.png");
    if (trinket01Surf)
    {
        trinket01Texture = SDL_CreateTextureFromSurface(rend, trinket01Surf);
        SDL_FreeSurface(trinket01Surf);
    }
    loadedTextures["Trinket01"] = trinket01Texture;

    //* T2 Items (No chests)

    SDL_Texture *sword02Texture = NULL;
    SDL_Surface *sword02Surf = IMG_Load("gfx/sword/Sword02.png");
    if (sword02Surf)
    {
        sword02Texture = SDL_CreateTextureFromSurface(rend, sword02Surf);
        SDL_FreeSurface(sword02Surf);
    }
    loadedTextures["Sword02"] = sword02Texture;

    SDL_Texture *armor02Texture = NULL;
    SDL_Surface *armor02Surf = IMG_Load("gfx/armor/Armor02.png");
    if (armor02Surf)
    {
        armor02Texture = SDL_CreateTextureFromSurface(rend, armor02Surf);
        SDL_FreeSurface(armor02Surf);
    }
    loadedTextures["Armor02"] = armor02Texture;

    SDL_Texture *trinket02Texture = NULL;
    SDL_Surface *trinket02Surf = IMG_Load("gfx/trinket/Trinket02.png");
    if (trinket02Surf)
    {
        trinket02Texture = SDL_CreateTextureFromSurface(rend, trinket02Surf);
        SDL_FreeSurface(trinket02Surf);
    }
    loadedTextures["Trinket02"] = trinket02Texture;
}

void Game::RemoveTextures()
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

Shop *Game::CreateShop(SDL_Renderer *rend, Player *plr)
{
    Shop *shop = new Shop(5, 3);
    shop->setPos(420, 20, rend);
    shop->setPlayerUsingShop(plr);

    //* T1

    //! Weapon

    //? Creating loot table for T1 Weapon Chest
    LootTable *weaponT1Loot = new LootTable();
    weaponT1Loot->setDMG(10, 30);
    weaponT1Loot->addValidType(ItemType::Weapon);

    //? Creating chest object
    Chest *chestWeapon1 = new Chest("Weapon Chest [T1]", Rarities::common, 15, loadedTextures["WeaponChest01"], weaponT1Loot);
    shop->addItem(chestWeapon1);

    //! Armor

    //? Creating loot table for T1 Armor Chest
    LootTable *armorT1Loot = new LootTable();
    armorT1Loot->setDEF(5, 10);
    armorT1Loot->addValidType(ItemType::Armor);

    //? Creating chest object
    Chest *chestArmor1 = new Chest("Armor Chest [T1]", Rarities::common, 15, loadedTextures["WeaponChest01"], armorT1Loot);
    shop->addItem(chestArmor1);

    //! Trinket

    //? Creating loot table for T1 Armor Chest
    LootTable *trinketT1Loot = new LootTable();
    trinketT1Loot->setHP(10, 20);
    trinketT1Loot->addValidType(ItemType::Trinket);

    //? Creating chest object
    Chest *chestTrinket1 = new Chest("Trinket Chest [T1]", Rarities::common, 15, loadedTextures["WeaponChest01"], trinketT1Loot);
    shop->addItem(chestTrinket1);

    //* T2

    //! Weapon

    //? Creating loot table for T1 Weapon Chest
    LootTable *weaponT2Loot = new LootTable();
    weaponT2Loot->setDMG(25, 50);
    weaponT2Loot->addValidType(ItemType::Weapon);

    //? Creating chest object
    Chest *chestWeapon2 = new Chest("Weapon Chest [T2]", Rarities::uncommon, 50, loadedTextures["WeaponChest01"], weaponT2Loot);
    chestWeapon2->setTier(2);
    shop->addItem(chestWeapon2);

    //! Armor

    //? Creating loot table for T1 Armor Chest
    LootTable *armorT2Loot = new LootTable();
    armorT2Loot->setDEF(10, 20);
    armorT2Loot->addValidType(ItemType::Armor);

    //? Creating chest object
    Chest *chestArmor2 = new Chest("Armor Chest [T2]", Rarities::uncommon, 50, loadedTextures["WeaponChest01"], armorT2Loot);
    chestArmor2->setTier(2);
    shop->addItem(chestArmor2);

    //! Trinket

    //? Creating loot table for T1 Armor Chest
    LootTable *trinketT2Loot = new LootTable();
    trinketT2Loot->setHP(20, 35);
    trinketT2Loot->addValidType(ItemType::Trinket);

    //? Creating chest object
    Chest *chestTrinket2 = new Chest("Trinket Chest [T2]", Rarities::uncommon, 50, loadedTextures["WeaponChest01"], trinketT2Loot);
    chestTrinket2->setTier(2);
    shop->addItem(chestTrinket2);

    return shop;
}

void Game::HandleLobbyLogic(SDL_Event &e, Inventory *playerInv, Shop *shop, UIButton *goArenaBtn)
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

void Game::HandleArenaLogic(SDL_Event &e, Arena *arena)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        bool wasActionCalled = false;
        if (!wasActionCalled)
        {
            if (arena->handleClickEvents())
            {
                wasActionCalled = true;
            }
        }
    }
}

Game::~Game()
{
    CleanUp();

    RemoveTextures();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();
}

Game::Game(int windowWidth, int windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    InitializeSDL(windowWidth, windowHeight, window, renderer, font);
    this->Init();
}

void Game::Init()
{

    //? Lobby Items

    player = new Player("Player", 100.0, 100.0);

    Inventory *playerInv = player->getInv();
    playerInv->setPos(20, 20, renderer);
    playerInv->setWindowSize(windowWidth, windowHeight);

    //? Adding starter sword
    Item *basicSword = new Weapon("Starter sword", Rarities::common, 0, loadedTextures["Sword01"], 1);
    playerInv->addItem(basicSword);

    shop = CreateShop(renderer, player);
    shop->setPos(windowWidth - shop->getWidth() - 20, 20, renderer);
    shop->setWindowSize(windowWidth, windowHeight);

    //? Arena stuff

    arena = new Arena(player);
    arena->calibrateWindowPos(windowWidth, windowHeight, renderer, font);

    goToArenaButton = new UIButton(200, 50, 50, 400, {255, 0, 0, 1}, "Go to Arena", font, renderer);
    goToArenaButton->setAction(
        [this]()
        {
            if (player->getInv()->getWeapon() != nullptr)
            {
                player->goToArena();
                arena->nextFight();
            }
        });

    //? Game loop
}

void Game::HandleEvents(SDL_Event e)
{
    if (this->arena->doRestart())
    {
        this->CleanUp();
        SDL_Delay(300);
        this->Init();
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
            HandleLobbyLogic(e, player->getInv(), shop, goToArenaButton);
        }
        else
        {
            HandleArenaLogic(e, arena);
        }
    }
}

void Game::Draw()
{
    SDL_SetRenderDrawColor(renderer, 74, 94, 224, SDL_ALPHA_OPAQUE); //? Sets background color
    SDL_RenderClear(renderer);

    if (player->getPlayerPosition() == PlayerPosition::Lobby)
    {
        player->getInv()->displaySDL(renderer);
        shop->displaySDL(renderer);
        goToArenaButton->display(renderer);
    }
    else
    {
        arena->display();
    }

    SDL_RenderPresent(renderer);
}

void Game::CleanUp()
{
    delete player;
    delete shop;
    delete goToArenaButton;
    delete arena;
}

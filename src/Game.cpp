#include <SDL2/SDL.h>

#include <Game.hpp>
#include <sstream>
#include <iomanip>

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

    //* Chests

    //? T1

    SDL_Texture *weaponChestT1Texture = NULL;
    SDL_Surface *weaponChestT1Surf = IMG_Load("gfx/chests/t1_Weapon.png");
    if (weaponChestT1Surf)
    {
        weaponChestT1Texture = SDL_CreateTextureFromSurface(rend, weaponChestT1Surf);
        SDL_FreeSurface(weaponChestT1Surf);
    }
    loadedTextures["WeaponChestT1"] = weaponChestT1Texture;

    SDL_Texture *armorChestT1Texture = NULL;
    SDL_Surface *armorChestT1Surf = IMG_Load("gfx/chests/t1_Armor.png");
    if (armorChestT1Surf)
    {
        armorChestT1Texture = SDL_CreateTextureFromSurface(rend, armorChestT1Surf);
        SDL_FreeSurface(armorChestT1Surf);
    }
    loadedTextures["ArmorChestT1"] = armorChestT1Texture;

    SDL_Texture *trinketChestT1Texture = NULL;
    SDL_Surface *trinketChestT1Surf = IMG_Load("gfx/chests/t1_Trinket.png");
    if (trinketChestT1Surf)
    {
        trinketChestT1Texture = SDL_CreateTextureFromSurface(rend, trinketChestT1Surf);
        SDL_FreeSurface(armorChestT1Surf);
    }
    loadedTextures["TrinketChestT1"] = trinketChestT1Texture;

    //? T2

    SDL_Texture *weaponChestT2Texture = NULL;
    SDL_Surface *weaponChestT2Surf = IMG_Load("gfx/chests/t2_Weapon.png");
    if (weaponChestT2Surf)
    {
        weaponChestT2Texture = SDL_CreateTextureFromSurface(rend, weaponChestT2Surf);
        SDL_FreeSurface(weaponChestT2Surf);
    }
    loadedTextures["WeaponChestT2"] = weaponChestT2Texture;

    SDL_Texture *armorChestT2Texture = NULL;
    SDL_Surface *armorChestT2Surf = IMG_Load("gfx/chests/t2_Armor.png");
    if (armorChestT2Surf)
    {
        armorChestT2Texture = SDL_CreateTextureFromSurface(rend, armorChestT2Surf);
        SDL_FreeSurface(armorChestT2Surf);
    }
    loadedTextures["ArmorChestT2"] = armorChestT2Texture;

    SDL_Texture *trinketChestT2Texture = NULL;
    SDL_Surface *trinketChestT2Surf = IMG_Load("gfx/chests/t2_Trinket.png");
    if (trinketChestT2Surf)
    {
        trinketChestT2Texture = SDL_CreateTextureFromSurface(rend, trinketChestT2Surf);
        SDL_FreeSurface(trinketChestT2Surf);
    }
    loadedTextures["TrinketChestT2"] = trinketChestT2Texture;

    //? T3

    SDL_Texture *weaponChestT3Texture = NULL;
    SDL_Surface *weaponChestT3Surf = IMG_Load("gfx/chests/t3_Weapon.png");
    if (weaponChestT3Surf)
    {
        weaponChestT3Texture = SDL_CreateTextureFromSurface(rend, weaponChestT3Surf);
        SDL_FreeSurface(weaponChestT3Surf);
    }
    loadedTextures["WeaponChestT3"] = weaponChestT3Texture;

    SDL_Texture *armorChestT3Texture = NULL;
    SDL_Surface *armorChestT3Surf = IMG_Load("gfx/chests/t3_Armor.png");
    if (armorChestT3Surf)
    {
        armorChestT3Texture = SDL_CreateTextureFromSurface(rend, armorChestT3Surf);
        SDL_FreeSurface(armorChestT3Surf);
    }
    loadedTextures["ArmorChestT3"] = armorChestT3Texture;

    SDL_Texture *trinketChestT3Texture = NULL;
    SDL_Surface *trinketChestT3Surf = IMG_Load("gfx/chests/t3_Trinket.png");
    if (trinketChestT3Surf)
    {
        trinketChestT3Texture = SDL_CreateTextureFromSurface(rend, trinketChestT3Surf);
        SDL_FreeSurface(trinketChestT3Surf);
    }
    loadedTextures["TrinketChestT3"] = trinketChestT3Texture;

    //? T4

    SDL_Texture *weaponChestT4Texture = NULL;
    SDL_Surface *weaponChestT4Surf = IMG_Load("gfx/chests/t4_Weapon.png");
    if (weaponChestT4Surf)
    {
        weaponChestT4Texture = SDL_CreateTextureFromSurface(rend, weaponChestT4Surf);
        SDL_FreeSurface(weaponChestT4Surf);
    }
    loadedTextures["WeaponChestT4"] = weaponChestT4Texture;

    SDL_Texture *armorChestT4Texture = NULL;
    SDL_Surface *armorChestT4Surf = IMG_Load("gfx/chests/t4_Armor.png");
    if (armorChestT4Surf)
    {
        armorChestT4Texture = SDL_CreateTextureFromSurface(rend, armorChestT4Surf);
        SDL_FreeSurface(armorChestT4Surf);
    }
    loadedTextures["ArmorChestT4"] = armorChestT4Texture;

    SDL_Texture *trinketChestT4Texture = NULL;
    SDL_Surface *trinketChestT4Surf = IMG_Load("gfx/chests/t4_Trinket.png");
    if (trinketChestT4Surf)
    {
        trinketChestT4Texture = SDL_CreateTextureFromSurface(rend, trinketChestT4Surf);
        SDL_FreeSurface(trinketChestT4Surf);
    }
    loadedTextures["TrinketChestT4"] = trinketChestT4Texture;

    //? T5

    SDL_Texture *weaponChestT5Texture = NULL;
    SDL_Surface *weaponChestT5Surf = IMG_Load("gfx/chests/t5_Weapon.png");
    if (weaponChestT5Surf)
    {
        weaponChestT5Texture = SDL_CreateTextureFromSurface(rend, weaponChestT5Surf);
        SDL_FreeSurface(weaponChestT5Surf);
    }
    loadedTextures["WeaponChestT5"] = weaponChestT5Texture;

    SDL_Texture *armorChestT5Texture = NULL;
    SDL_Surface *armorChestT5Surf = IMG_Load("gfx/chests/t5_Armor.png");
    if (armorChestT5Surf)
    {
        armorChestT5Texture = SDL_CreateTextureFromSurface(rend, armorChestT5Surf);
        SDL_FreeSurface(armorChestT5Surf);
    }
    loadedTextures["ArmorChestT5"] = armorChestT5Texture;

    SDL_Texture *trinketChestT5Texture = NULL;
    SDL_Surface *trinketChestT5Surf = IMG_Load("gfx/chests/t5_Trinket.png");
    if (trinketChestT5Surf)
    {
        trinketChestT5Texture = SDL_CreateTextureFromSurface(rend, trinketChestT5Surf);
        SDL_FreeSurface(trinketChestT5Surf);
    }
    loadedTextures["TrinketChestT5"] = trinketChestT5Texture;

    //* Mobs

    SDL_Texture *mob01Texture = NULL;
    SDL_Surface *mob01Surf = IMG_Load("gfx/mobs/Mob01.png");
    if (mob01Surf)
    {
        mob01Texture = SDL_CreateTextureFromSurface(rend, mob01Surf);
        SDL_FreeSurface(mob01Surf);
    }
    loadedTextures["Mob01"] = mob01Texture;

    SDL_Texture *mob02Texture = NULL;
    SDL_Surface *mob02Surf = IMG_Load("gfx/mobs/Mob02.png");
    if (mob02Surf)
    {
        mob02Texture = SDL_CreateTextureFromSurface(rend, mob02Surf);
        SDL_FreeSurface(mob02Surf);
    }
    loadedTextures["Mob02"] = mob02Texture;

    SDL_Texture *mob03Texture = NULL;
    SDL_Surface *mob03Surf = IMG_Load("gfx/mobs/Mob03.png");
    if (mob03Surf)
    {
        mob03Texture = SDL_CreateTextureFromSurface(rend, mob03Surf);
        SDL_FreeSurface(mob03Surf);
    }
    loadedTextures["Mob03"] = mob03Texture;

    SDL_Texture *mob04Texture = NULL;
    SDL_Surface *mob04Surf = IMG_Load("gfx/mobs/Mob04.png");
    if (mob04Surf)
    {
        mob04Texture = SDL_CreateTextureFromSurface(rend, mob04Surf);
        SDL_FreeSurface(mob04Surf);
    }
    loadedTextures["Mob04"] = mob04Texture;

    SDL_Texture *mob05Texture = NULL;
    SDL_Surface *mob05Surf = IMG_Load("gfx/mobs/Mob05.png");
    if (mob05Surf)
    {
        mob05Texture = SDL_CreateTextureFromSurface(rend, mob05Surf);
        SDL_FreeSurface(mob05Surf);
    }
    loadedTextures["Mob05"] = mob05Texture;

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

    //* T3 Items (No chests)

    SDL_Texture *sword03Texture = NULL;
    SDL_Surface *sword03Surf = IMG_Load("gfx/sword/Sword03.png");
    if (sword03Surf)
    {
        sword03Texture = SDL_CreateTextureFromSurface(rend, sword03Surf);
        SDL_FreeSurface(sword03Surf);
    }
    loadedTextures["Sword03"] = sword03Texture;

    SDL_Texture *armor03Texture = NULL;
    SDL_Surface *armor03Surf = IMG_Load("gfx/armor/Armor03.png");
    if (armor03Surf)
    {
        armor03Texture = SDL_CreateTextureFromSurface(rend, armor03Surf);
        SDL_FreeSurface(armor03Surf);
    }
    loadedTextures["Armor03"] = armor03Texture;

    SDL_Texture *trinket03Texture = NULL;
    SDL_Surface *trinket03Surf = IMG_Load("gfx/trinket/Trinket03.png");
    if (trinket03Surf)
    {
        trinket03Texture = SDL_CreateTextureFromSurface(rend, trinket03Surf);
        SDL_FreeSurface(trinket03Surf);
    }
    loadedTextures["Trinket03"] = trinket03Texture;

    //* T4 Items (No chests)

    SDL_Texture *sword04Texture = NULL;
    SDL_Surface *sword04Surf = IMG_Load("gfx/sword/Sword04.png");
    if (sword04Surf)
    {
        sword04Texture = SDL_CreateTextureFromSurface(rend, sword04Surf);
        SDL_FreeSurface(sword04Surf);
    }
    loadedTextures["Sword04"] = sword04Texture;

    SDL_Texture *armor04Texture = NULL;
    SDL_Surface *armor04Surf = IMG_Load("gfx/armor/Armor04.png");
    if (armor04Surf)
    {
        armor04Texture = SDL_CreateTextureFromSurface(rend, armor04Surf);
        SDL_FreeSurface(armor04Surf);
    }
    loadedTextures["Armor04"] = armor04Texture;

    SDL_Texture *trinket04Texture = NULL;
    SDL_Surface *trinket04Surf = IMG_Load("gfx/trinket/Trinket04.png");
    if (trinket04Surf)
    {
        trinket04Texture = SDL_CreateTextureFromSurface(rend, trinket04Surf);
        SDL_FreeSurface(trinket04Surf);
    }
    loadedTextures["Trinket04"] = trinket04Texture;

    //* T5 Items (No chests)

    SDL_Texture *sword05Texture = NULL;
    SDL_Surface *sword05Surf = IMG_Load("gfx/sword/Sword05.png");
    if (sword05Surf)
    {
        sword05Texture = SDL_CreateTextureFromSurface(rend, sword05Surf);
        SDL_FreeSurface(sword05Surf);
    }
    loadedTextures["Sword05"] = sword05Texture;

    SDL_Texture *armor05Texture = NULL;
    SDL_Surface *armor05Surf = IMG_Load("gfx/armor/Armor05.png");
    if (armor05Surf)
    {
        armor05Texture = SDL_CreateTextureFromSurface(rend, armor05Surf);
        SDL_FreeSurface(armor05Surf);
    }
    loadedTextures["Armor05"] = armor05Texture;

    SDL_Texture *trinket05Texture = NULL;
    SDL_Surface *trinket05Surf = IMG_Load("gfx/trinket/Trinket05.png");
    if (trinket05Surf)
    {
        trinket05Texture = SDL_CreateTextureFromSurface(rend, trinket05Surf);
        SDL_FreeSurface(trinket05Surf);
    }
    loadedTextures["Trinket05"] = trinket05Texture;
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
    Chest *chestWeapon1 = new Chest("Weapon Chest [T1]", Rarities::common, 15, loadedTextures["WeaponChestT1"], weaponT1Loot);
    shop->addItem(chestWeapon1);

    //! Armor

    //? Creating loot table for T1 Armor Chest
    LootTable *armorT1Loot = new LootTable();
    armorT1Loot->setDEF(5, 10);
    armorT1Loot->addValidType(ItemType::Armor);

    //? Creating chest object
    Chest *chestArmor1 = new Chest("Armor Chest [T1]", Rarities::common, 15, loadedTextures["ArmorChestT1"], armorT1Loot);
    shop->addItem(chestArmor1);

    //! Trinket

    //? Creating loot table for T1 Armor Chest
    LootTable *trinketT1Loot = new LootTable();
    trinketT1Loot->setHP(10, 20);
    trinketT1Loot->addValidType(ItemType::Trinket);

    //? Creating chest object
    Chest *chestTrinket1 = new Chest("Trinket Chest [T1]", Rarities::common, 15, loadedTextures["TrinketChestT1"], trinketT1Loot);
    shop->addItem(chestTrinket1);

    //* T2

    //! Weapon

    //? Creating loot table for T1 Weapon Chest
    LootTable *weaponT2Loot = new LootTable();
    weaponT2Loot->setDMG(25, 50);
    weaponT2Loot->addValidType(ItemType::Weapon);

    //? Creating chest object
    Chest *chestWeapon2 = new Chest("Weapon Chest [T2]", Rarities::uncommon, 50, loadedTextures["WeaponChestT2"], weaponT2Loot);
    chestWeapon2->setTier(2);
    shop->addItem(chestWeapon2);

    //! Armor

    //? Creating loot table for T1 Armor Chest
    LootTable *armorT2Loot = new LootTable();
    armorT2Loot->setDEF(10, 20);
    armorT2Loot->addValidType(ItemType::Armor);

    //? Creating chest object
    Chest *chestArmor2 = new Chest("Armor Chest [T2]", Rarities::uncommon, 50, loadedTextures["ArmorChestT2"], armorT2Loot);
    chestArmor2->setTier(2);
    shop->addItem(chestArmor2);

    //! Trinket

    //? Creating loot table for T1 Armor Chest
    LootTable *trinketT2Loot = new LootTable();
    trinketT2Loot->setHP(20, 35);
    trinketT2Loot->addValidType(ItemType::Trinket);

    //? Creating chest object
    Chest *chestTrinket2 = new Chest("Trinket Chest [T2]", Rarities::uncommon, 50, loadedTextures["TrinketChestT2"], trinketT2Loot);
    chestTrinket2->setTier(2);
    shop->addItem(chestTrinket2);

    //* T3

    //! Weapon

    //? Creating loot table for T3 Weapon Chest
    LootTable *weaponT3Loot = new LootTable();
    weaponT3Loot->setDMG(40, 80);
    weaponT3Loot->addValidType(ItemType::Weapon);

    //? Creating chest object
    Chest *chestWeapon3 = new Chest("Weapon Chest [T3]", Rarities::rare, 100, loadedTextures["WeaponChestT3"], weaponT3Loot);
    chestWeapon3->setTier(3);
    shop->addItem(chestWeapon3);

    //! Armor

    //? Creating loot table for T3 Armor Chest
    LootTable *armorT3Loot = new LootTable();
    armorT3Loot->setDEF(20, 30);
    armorT3Loot->addValidType(ItemType::Armor);

    //? Creating chest object
    Chest *chestArmor3 = new Chest("Armor Chest [T3]", Rarities::rare, 100, loadedTextures["ArmorChestT3"], armorT3Loot);
    chestArmor3->setTier(3);
    shop->addItem(chestArmor3);

    //! Trinket

    //? Creating loot table for T3 Trinket Chest
    LootTable *trinketT3Loot = new LootTable();
    trinketT3Loot->setHP(40, 60);
    trinketT3Loot->addValidType(ItemType::Trinket);

    //? Creating chest object
    Chest *chestTrinket3 = new Chest("Trinket Chest [T3]", Rarities::rare, 100, loadedTextures["TrinketChestT3"], trinketT3Loot);
    chestTrinket3->setTier(3);
    shop->addItem(chestTrinket3);

    //* T4

    //! Weapon

    //? Creating loot table for T4 Weapon Chest
    LootTable *weaponT4Loot = new LootTable();
    weaponT4Loot->setDMG(70, 100);
    weaponT4Loot->addValidType(ItemType::Weapon);

    //? Creating chest object
    Chest *chestWeapon4 = new Chest("Weapon Chest [T4]", Rarities::epic, 200, loadedTextures["WeaponChestT4"], weaponT4Loot);
    chestWeapon4->setTier(4);
    shop->addItem(chestWeapon4);

    //! Armor

    //? Creating loot table for T4 Armor Chest
    LootTable *armorT4Loot = new LootTable();
    armorT4Loot->setDEF(30, 40);
    armorT4Loot->addValidType(ItemType::Armor);

    //? Creating chest object
    Chest *chestArmor4 = new Chest("Armor Chest [T4]", Rarities::epic, 200, loadedTextures["ArmorChestT4"], armorT4Loot);
    chestArmor4->setTier(4);
    shop->addItem(chestArmor4);

    //! Trinket

    //? Creating loot table for T4 Trinket Chest
    LootTable *trinketT4Loot = new LootTable();
    trinketT4Loot->setHP(60, 80);
    trinketT4Loot->addValidType(ItemType::Trinket);

    //? Creating chest object
    Chest *chestTrinket4 = new Chest("Trinket Chest [T4]", Rarities::epic, 200, loadedTextures["TrinketChestT4"], trinketT4Loot);
    chestTrinket4->setTier(4);
    shop->addItem(chestTrinket4);

    //* T5

    //! Weapon

    //? Creating loot table for T5 Weapon Chest
    LootTable *weaponT5Loot = new LootTable();
    weaponT5Loot->setDMG(95, 120);
    weaponT5Loot->addValidType(ItemType::Weapon);

    //? Creating chest object
    Chest *chestWeapon5 = new Chest("Weapon Chest [T5]", Rarities::legendary, 500, loadedTextures["WeaponChestT5"], weaponT5Loot);
    chestWeapon5->setTier(5);
    shop->addItem(chestWeapon5);

    //! Armor

    //? Creating loot table for T5 Armor Chest
    LootTable *armorT5Loot = new LootTable();
    armorT5Loot->setDEF(40, 50);
    armorT5Loot->addValidType(ItemType::Armor);

    //? Creating chest object
    Chest *chestArmor5 = new Chest("Armor Chest [T5]", Rarities::legendary, 500, loadedTextures["ArmorChestT5"], armorT5Loot);
    chestArmor5->setTier(5);
    shop->addItem(chestArmor5);

    //! Trinket

    //? Creating loot table for T5 Trinket Chest
    LootTable *trinketT5Loot = new LootTable();
    trinketT5Loot->setHP(80, 100);
    trinketT5Loot->addValidType(ItemType::Trinket);

    //? Creating chest object
    Chest *chestTrinket5 = new Chest("Trinket Chest [T5]", Rarities::legendary, 500, loadedTextures["TrinketChestT5"], trinketT5Loot);
    chestTrinket5->setTier(5);
    shop->addItem(chestTrinket5);

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

                std::stringstream stream;

                stream.str("");
                stream.clear();
                stream << std::fixed << std::setprecision(1) << playerInv->getHP();
                std::string HPString = "HP: " + stream.str();

                playerStats->getElement(2)->setText(HPString, font, renderer);

                if (playerInv->getWeapon())
                {
                    stream.str("");
                    stream.clear();
                    stream << std::fixed << std::setprecision(1) << playerInv->getWeapon()->getDamage();
                    std::string DMGString = "DMG: " + stream.str();

                    playerStats->getElement(3)->setText(DMGString, font, renderer);
                }
                else
                {
                    playerStats->getElement(3)->setText("DMG: 0", font, renderer);
                }

                if (playerInv->getArmor())
                {
                    stream.str("");
                    stream.clear();
                    stream << std::fixed << std::setprecision(1) << playerInv->getArmor()->getDEF();
                    std::string DMGString = "DEF: " + stream.str();

                    playerStats->getElement(4)->setText(DMGString, font, renderer);
                }
                else
                {
                    playerStats->getElement(4)->setText("DEF: 0", font, renderer);
                }
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

    std::string tierText = "LVL: " + std::to_string(player->getLvl()) + " / TIER: " + std::to_string(player->getTier());
    tierDisplay = new UIElement(shop->getWidth(), 35, shop->getPosX(), shop->getPosY() + shop->getHeight() + 20, {153, 154, 158, SDL_ALPHA_OPAQUE}, tierText, font, renderer);

    //? Arena stuff

    arena = new Arena(player);
    arena->calibrateWindowPos(windowWidth, windowHeight, renderer, font);
    arena->setLobbyTierText(tierDisplay);

    playerStats = new UIGroup(playerInv->getPosX(), playerInv->getPosY() + playerInv->getHeight() + 20);

    UIElement *playerStatsBG = new UIElement(playerInv->getWidth(), 90, 0, 0, {153, 154, 158, 1});
    playerStats->addElement(playerStatsBG);

    UIElement *playerStatsText = new UIElement(playerInv->getWidth(), 30, 0, 0, {153, 154, 158, 1}, "Your stats:", font, renderer);
    playerStats->addElement(playerStatsText);

    UIElement *playerHPText = new UIElement(playerInv->getWidth(), 30, 0, 30, {153, 154, 158, 1}, "HP: 100.0", font, renderer);
    playerStats->addElement(playerHPText);

    UIElement *playerDMGText = new UIElement(playerInv->getWidth(), 30, 0, 60, {153, 154, 158, 1}, "DMG: 0", font, renderer);
    playerStats->addElement(playerDMGText);

    UIElement *playerDEFText = new UIElement(playerInv->getWidth(), 30, 0, 90, {153, 154, 158, 1}, "DEF: 0", font, renderer);
    playerStats->addElement(playerDEFText);

    goToArenaButton = new UIButton(200, 50, 20, windowHeight - 70, {255, 0, 0, 1}, "Go to Arena", font, renderer);
    goToArenaButton->setAction(
        [this]()
        {
            if (player->getInv()->getWeapon() != nullptr)
            {
                player->getInv()->setTempHP(player->getInv()->getHP());
                player->goToArena();
                arena->nextFight();
            }
        });
}

void Game::HandleEvents(SDL_Event e)
{
    if (this->arena->doRestart())
    {
        this->CleanUp();
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
        tierDisplay->display(renderer);
        playerStats->display(renderer);
        goToArenaButton->display(renderer);
        player->getInv()->displaySDL(renderer);
        shop->displaySDL(renderer);
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
    delete tierDisplay;
    delete playerStats;
}

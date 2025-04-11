#pragma once

#include <SDL2/SDL.h>
#include <UIButton.hpp>
#include <UIElement.hpp>
#include <UIImage.hpp>
#include <UIButton.hpp>
#include <UIButtonImage.hpp>
#include <UIGroup.hpp>

#include <Weapon.hpp>
#include <Armor.hpp>
#include <Trinket.hpp>

#include <Item.hpp>
#include <Weapon.hpp>
#include <Armor.hpp>
#include <Trinket.hpp>

#include <vector>

class Inventory
{
protected:
    enum ItemParameter
    {
        weapon,
        armor,
        trinket
    };
    //? Logic Stuff
    int rows, cols;
    Item ***items;
    Item *equipedWeapon;
    Item *equipedArmor;
    Item *equipedTrinket;

    bool isMoveMode = false;
    int moveOriginRow = -1;
    int moveOriginCol = -1;

    //? UI Stuff
    SDL_Renderer *rend;
    const SDL_Color inventoryBGColor = {116, 117, 125, SDL_ALPHA_OPAQUE};

    std::vector<UIButton *> menuButtons;
    std::vector<UIButton *> slotButtons;

    int posX, posY;

    bool isUIGenerated = false;
    UIElement *inventoryBG;
    UIButtonImage ***UIInventorySlots;
    UIGroup *menu = nullptr;

    const int PADDING = 10;
    const int SLOT_SIZE = 50;
    const int SLOT_PADDING = 1;
    const int MENU_BUTTON_WIDTH = 70;
    const int MENU_BUTTON_HEIGHT = 40;

    void defaultSlotAction(int row, int col);
    void testAction(int row, int col);

public:
    Inventory(int rows, int cols);
    ~Inventory();

    void displayCLI();
    void displaySDL(SDL_Renderer *rend);
    void generateUIElements();

    bool handleClickEvents();
    bool removeMenu();

    void enableMoveMode(int row, int col);
    void disableMoveMode();

    bool addItem(Item *item);
    void sortItems(char parameter);
    bool moveItems(int oldRow, int oldCol, int newRow, int newCol);
    void removeItem(int row, int col);
    void equipItem(Weapon *weapon);
    void equipItem(Trinket *trinket);
    void equipItem(Armor *armor);
    void unequipItem(ItemParameter parameter);
    void useItem(int row, int col);
    bool toggleFavourite(int row, int col);

    int getCols();
    int getRows();
    void setPos(int posX, int posY, SDL_Renderer *rend);

    bool hasFreeSlot();
};

//? https://www.youtube.com/watch?v=OjNpRbNdR7E

//! Krzychu approved

// Tiānshàng tàiyang hóng ya hóngtōngtōng ēi
// Xīnzhōng de tàiyang shì máozédōng ēi
// Tā lǐngdǎo wǒmen dé jiěfàng ēi
// Rénmín fānshēn dāngjiāzuòzhǔ rén
// Yīya yī zhī yōu wèi
// Ya ér ya zhī yōu ā
// Rénmín fānshēn dāngjiāzuòzhǔ rén

// Tiānshàng tàiyang hóng ya hóngtōngtōng ēi
// Xīnzhōng de tàiyang shì máozédōng ēi
// Tā lǐngdǎo wǒmen fènyǒng xiàngqián jìn ēi
// Gémìng jiāngshān yì yē yí piàn hóng ēi
// Yīya yī zhī yōu wèi
// Ya ér ya zhī yōu ā
// Gémìng jiāngshān yí piàn hóng

// Wǒmen xīnzhōng de hóng tàiyang
// Zhàodé biānjiāng yí piàn hóng
// Cháng bǎi qiānlǐ gēshēng liáoliàng
// Hǎi lán jiāngpàn hóngqí fēiyáng
// Qiān tiáo jiānghé guī dàhǎi
// Wàn duǒ kuíhuā xiàngyáng kāi
// Yánbiān rénmín zòngqíng gēchàng
// Wǒmen xīnzhōng de hóng tàiyang
// Āi… máozhǔxí
// Wǒmen wúxiàn rèài nín
// Nínde jiàodǎo láojì xīnshàng
// Yánbiān rénmín zhùyuàn nín
// Wànshòuwújiāng wànshòuwújiāng
// See pop shows near Lodz
// Get tickets as low as $70
// You might also like
// 屠洪刚 (Tu Honggang) - 天上太阳红彤彤 (Red Sun in the Sky) [English Translation]
// Genius English Translations
// 天上太阳红彤彤 (Red Sun In The Sky)
// 屠洪刚 (Tu Honggang)
// Sticky
// Tyler, The Creator
// Tiānshàng tàiyang hóng ya hóngtōngtōng ēi
// Xīnzhōng de tàiyang shì máozédōng ēi
// Tā lǐngdǎo wǒmen dé jiěfàng ēi
// Rénmín fānshēn dāngjiāzuòzhǔ rén
// Yīya yī zhī yōu wèi
// Ya ér ya zhī yōu ā
// Rénmín fānshēn dāngjiāzuòzhǔ rén

// Tiānshàng tàiyang hóng ya hóngtōngtōng ēi
// Xīnzhōng de tàiyang shì máozédōng ēi
// Tā lǐngdǎo wǒmen fènyǒng xiàngqián jìn ēi
// Gémìng jiāngshān yì yē yí piàn hóng ēi
// Yīya yī zhī yōu wèi
// Ya ér ya zhī yōu ā
// Gémìng jiāngshān yí piàn hóng

// Tiānshàng tàiyang hóng ya hóngtōngtōng ēi
// Xīnzhōng de tàiyang shì máozédōng ēi
// Tā lǐngdǎo wǒmen dé jiěfàng ēi
// Tā lǐngdǎo wǒmen fènyǒngqiánjìn ēi
// Gémìng jiāngshān yì ya yí piàn hóng ēi
// Suō lā lā zǐ suō lā lā zǐ
// Yì ya yí piàn hóng ēi
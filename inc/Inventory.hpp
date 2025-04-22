#pragma once

#include <SDL2/SDL.h>
#include <UIButton.hpp>
#include <UIElement.hpp>
#include <UIImage.hpp>
#include <UIButton.hpp>
#include <UIButtonImage.hpp>
#include <UIGroup.hpp>

#include <Item.hpp>
#include <Weapon.hpp>
#include <Armor.hpp>
#include <Trinket.hpp>
#include <Chest.hpp>

#include <Enums.hpp>

#include <vector>

class Inventory
{
protected:
    //? Logic Stuff
    int rows, cols;
    Item ***items;
    Weapon *equipedWeapon;
    Armor *equipedArmor;
    Trinket *equipedTrinket;

    bool isMoveMode = false;
    int moveOriginRow = -1;
    int moveOriginCol = -1;

    float HP, tempHP, gold;

    //? UI Stuff
    SDL_Renderer *rend;
    const SDL_Color inventoryBGColor = {116, 117, 125, SDL_ALPHA_OPAQUE};

    std::vector<UIButton *> menuButtons;
    std::vector<UIButton *> slotButtons;

    int posX, posY;
    int windowWidth, windowHeight;
    int invWidth, invHeight;

    bool isUIGenerated = false;
    UIElement *inventoryBG;
    UIElement *inventoryTitle;
    UIElement *goldText;
    UIButtonImage ***UIInventorySlots;
    UIGroup *menu = nullptr;

    const int PADDING_TOP = 15;
    const int PADDING = 10;
    const int SLOT_SIZE = 50;
    const int SLOT_PADDING = 1;
    const int MENU_BUTTON_WIDTH = 100; //! Not used anymore
    const int MENU_BUTTON_HEIGHT = 35;
    const int MENU_PADDING_RIGHT = 5;

    std::string inventoryName = "Inventory";

    virtual void defaultSlotAction(int row, int col);
    bool openChest(int row, int col);
    void calculateMenuElementDimentions(int &maxWidth, SDL_Texture *texutre);

public:
    Inventory(int rows, int cols);
    virtual ~Inventory();

    void displayCLI();
    void virtual displaySDL(SDL_Renderer *rend);
    void generateUIElements();

    virtual bool handleClickEvents();
    bool removeMenu();

    void enableMoveMode(int row, int col);
    void disableMoveMode();

    bool addItem(Item *item);
    void sortItems(char parameter);
    bool moveItems(int oldRow, int oldCol, int newRow, int newCol);
    void removeItem(int row, int col);
    Item *takeItemOut(int row, int col);
    void equipItem(Weapon *weapon);
    void equipItem(Trinket *trinket);
    void equipItem(Armor *armor);
    void unequipItem(ItemType parameter);
    void useItem(int row, int col);
    bool toggleFavourite(int row, int col);

    void setPos(int posX, int posY, SDL_Renderer *rend);
    void setWindowSize(int x, int y);

    int getCols();
    int getRows();
    int getWidth();
    int getHeight();
    int getPosX();
    int getPosY();

    void setHP(float maxHP);
    void setTempHP(float HP);
    void setGold(float gold);

    float getHP();
    float getTempHP();
    float getGold();

    Weapon *getWeapon();
    Armor *getArmor();
    Trinket *getTrinket();

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
// Xīnzhōng de tàiyang shì máozédōng ēi 🌸🌷🌻
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
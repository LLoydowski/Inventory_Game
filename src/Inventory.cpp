#include <Inventory.hpp>
#include <UIElement.hpp>
#include <UIButton.hpp>
#include <UIImage.hpp>

#include "Weapon.hpp"
#include "Armor.hpp"
#include "Trinket.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <vector>

Inventory::Inventory(int rows, int cols) : rows{rows}, cols{cols}, equipedWeapon{nullptr}, equipedArmor{nullptr}, equipedTrinket{nullptr}
{

    // Generating item 2D array
    items = new Item **[rows];

    for (int i = 0; i < rows; i++)
    {
        items[i] = new Item *[cols];
        for (int j = 0; j < cols; j++)
        {
            items[i][j] = nullptr;
        }
    }

    UIInventorySlots = new UIImage **[rows];

    for (int i = 0; i < rows; i++)
    {
        UIInventorySlots[i] = new UIImage *[cols];
        for (int j = 0; j < cols; j++)
        {
            UIInventorySlots[i][j] = nullptr;
        }
    }

    posX = -1;
    posY = -1;
}
Inventory::~Inventory()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (items[i][j] != nullptr)
            {
                delete items[i][j];
            }
        }
        delete[] items[i];
    }
    delete[] items;

    delete inventoryBG;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (UIInventorySlots[i][j] != nullptr)
            {
                delete UIInventorySlots[i][j];
            }
        }
        delete[] UIInventorySlots[i];
    }
    delete[] UIInventorySlots;

    SDL_DestroyTexture(nullTexture);
}
void Inventory::displayCLI()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << "[";
            if (items[i][j] != nullptr)
            {
                std::cout << items[i][j]->getName()[0];
            }
            else
            {
                std::cout << " ";
            }
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}
void Inventory::displaySDL(SDL_Renderer *rend)
{
    if (posX == -1 || posY == -1)
    {
        std::cout << "You need to set position first ( setPos(posX, posY); )" << std::endl;
        return;
    }

    inventoryBG->display(rend);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (UIInventorySlots[i][j] != nullptr)
            {
                UIInventorySlots[i][j]->display(rend, PADDING);
            }
        }
    }
}
void Inventory::generateUIElements()
{

    if (!rend)
    {
        std::cout << "[Inventory] ERROR: No renderer set." << std::endl;
        return;
    }

    const int width = (cols * (PADDING + SLOT_SIZE)) + PADDING;
    const int height = (rows * (PADDING + SLOT_SIZE)) + PADDING;

    inventoryBG = new UIElement(width, height, posX, posY, inventoryBGColor);

    nullTexture = NULL;
    // SDL_Surface *nullSurf = IMG_Load("gfx/placeholder.png");
    // if (nullSurf)
    // {
    //     nullTexture = SDL_CreateTextureFromSurface(rend, nullSurf);
    //     SDL_FreeSurface(nullSurf);
    // }

    // blankSlotTexture = NULL;
    // SDL_Surface *blankSLotSurface = IMG_Load("gfx/placeholder.png");
    // if (!blankSLotSurface)
    // {
    //     std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    //     return;
    // }

    // blankSlotTexture = SDL_CreateTextureFromSurface(rend, blankSLotSurface);
    // SDL_FreeSurface(blankSLotSurface);

    // if (!blankSlotTexture)
    // {
    //     std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    //     return;
    // }

    int wholeOffsetY = posY + PADDING;
    for (int i = 0; i < rows; i++)
    {
        int wholeOffsetX = posX + PADDING;
        for (int j = 0; j < cols; j++)
        {
            if (UIInventorySlots[i][j] != nullptr)
            {
                delete UIInventorySlots[i][j];
            }

            SDL_Color bgColor = {153, 154, 158, SDL_ALPHA_OPAQUE};
            UIInventorySlots[i][j] = new UIImage(SLOT_SIZE, SLOT_SIZE, wholeOffsetX, wholeOffsetY, nullTexture, bgColor);

            wholeOffsetX += PADDING + SLOT_SIZE;
        }
        wholeOffsetY += PADDING + SLOT_SIZE;
    }
}

bool Inventory::addItem(Item *item)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (items[i][j] == nullptr)
            {
                items[i][j] = item;

                SDL_Texture *texture = nullTexture;
                SDL_Texture *itemTexture = item->getTexture();
                if (itemTexture != nullptr)
                {
                    texture = itemTexture;
                }

                UIInventorySlots[i][j]->setTexture(texture);

                return true;
            }
        }
    }
    return false;
}

void Inventory::removeItem(int row, int col)
{
    delete items[row][col];
    items[row][col] = nullptr;
}

bool Inventory::moveItems(int oldRow, int oldCol, int newRow, int newCol)
{

    if (oldRow < 0 || oldRow > rows || newRow < 0 || newRow > rows || oldCol < 0 || oldCol > cols || newCol < 0 || newCol > cols)
    {
        return false;
    }

    Item *tempItem = items[oldRow][oldCol];
    items[oldRow][oldCol] = items[newRow][newCol];
    items[newRow][newCol] = tempItem;
    return true;
}

void Inventory::sortItems(char parameter)
{
    std::vector<Item *> itemList;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (items[i][j] != nullptr)
            {
                itemList.push_back(items[i][j]);
            }
        }
    }

    int n = itemList.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            bool shouldSwap = false;

            if (parameter == 'p')
            {
                shouldSwap = itemList[j]->getPrice() > itemList[j + 1]->getPrice();
            }
            else if (parameter == 'n')
            {
                shouldSwap = itemList[j]->getName() > itemList[j + 1]->getName();
            }
            else if (parameter == 'r')
            {
                shouldSwap = itemList[j]->getRarity() > itemList[j + 1]->getRarity();
            }
            else if (parameter == 'f')
            {
                shouldSwap = !itemList[j]->getFavourite() && itemList[j + 1]->getFavourite();
            }

            if (shouldSwap)
            {
                std::swap(itemList[j], itemList[j + 1]);
            }
        }
    }
}

bool Inventory::toggleFavourite(int row, int col)
{
    if (dynamic_cast<Item *>(items[col][row]) == nullptr)
    {
        return false;
    }

    if (items[row][col]->getFavourite())
    {
        items[row][col]->setFavourite(true);
    }
    else
    {
        items[row][col]->setFavourite(false);
    }
    return true;
}

// -------------ITEM MUSI MIEĆ VIRTUAL FUNCTION (polimorfizm te sprawy)

void Inventory::equipItem(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return;
    }

    Item* item = items[row][col];

    if (item == nullptr) {
        return;
    }

    if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {

        if (equipedWeapon != nullptr) {
            addItem(equipedWeapon);
        }

        equipedWeapon = weapon;
        items[row][col] = nullptr;
    }
    else if (Armor* armor = dynamic_cast<Armor*>(item)) {

        if (equipedArmor != nullptr) {
            addItem(equipedArmor);
        }

        equipedArmor = armor;
        items[row][col] = nullptr;
    }
    else if (Trinket* trinket = dynamic_cast<Trinket*>(item)) {

        if (equipedTrinket != nullptr) {
            addItem(equipedTrinket);
        }

        equipedTrinket = trinket;
        items[row][col] = nullptr;
    }
}


int Inventory::getCols()
{
    return cols;
}

int Inventory::getRows()
{
    return rows;
}

void Inventory::setPos(int posX, int posY, SDL_Renderer *rend)
{
    this->posX = posX;
    this->posY = posY;
    this->rend = rend;
    generateUIElements();
}

bool Inventory::hasFreeSlot()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (items[i][j] == nullptr)
            {
                return true;
            }
        }
    }
    return false;
}

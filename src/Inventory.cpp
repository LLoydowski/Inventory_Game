#include <Inventory.hpp>
#include <UIElement.hpp>
#include <UIButton.hpp>
#include <UIImage.hpp>
#include <UIButtonImage.hpp>

#include "Weapon.hpp"
#include "Armor.hpp"
#include "Trinket.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <vector>

void Inventory::defaultSlotAction(int row, int col)
{
    // std::cout << "[Inventory] Success: This is a default action\n";

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    this->removeMenu();

    menu = new UIGroup(mouseX, mouseY);

    SDL_Color color = {200, 200, 200, 255};

    UIElement *bg = new UIElement(100, 300, 0, 0, color);
    menu->addElement(bg);

    TTF_Font *font = TTF_OpenFont("font/OpenSans.ttf", 72);
    if (font == nullptr)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    UIButton *moveButton = new UIButton(100, 50, 0, 0, color, "Move item", font, rend);
    moveButton->setAction([this, row, col]()
                          { testAction(row, col); });
    menuButtons.push_back(moveButton);
    menu->addElement(moveButton);

    TTF_CloseFont(font);

    menu->setPos(mouseX, mouseY);
}

void Inventory::testAction(int row, int col)
{
    std::cout << "[Inventory] Success: This is a test action\n";
    std::cout << "Row: " << row << "\nCol: " << col << std::endl;
}

Inventory::Inventory(int rows, int cols) : rows{rows}, cols{cols}, equipedWeapon{nullptr}, equipedArmor{nullptr}, equipedTrinket{nullptr}
{

    // Generating item 2D array
    items = new Item **[rows];
    UIInventorySlots = new UIButtonImage **[rows];

    for (int i = 0; i < rows; i++)
    {
        items[i] = new Item *[cols];
        UIInventorySlots[i] = new UIButtonImage *[cols];
        for (int j = 0; j < cols; j++)
        {
            items[i][j] = nullptr;
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
                items[i][j] = nullptr;
            }
        }
        delete[] items[i];
    }
    delete[] items;

    delete inventoryBG;
    inventoryBG = nullptr;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (UIInventorySlots[i][j] != nullptr)
            {
                delete UIInventorySlots[i][j];
                UIInventorySlots[i][j] = nullptr;
            }
        }
    }

    delete[] UIInventorySlots;
    UIInventorySlots = nullptr;

    delete menu;
    menu = nullptr;
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

    if (menu != nullptr)
    {
        menu->display(rend);
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

    int wholeOffsetY = posY + PADDING;
    for (int i = 0; i < rows; i++)
    {
        int wholeOffsetX = posX + PADDING;
        for (int j = 0; j < cols; j++)
        {
            if (UIInventorySlots[i][j] != nullptr && UIInventorySlots[i][j] != NULL)
            {
                delete UIInventorySlots[i][j];
            }

            SDL_Color bgColor = {153, 154, 158, SDL_ALPHA_OPAQUE};
            UIButtonImage *button = new UIButtonImage(SLOT_SIZE, SLOT_SIZE, wholeOffsetX, wholeOffsetY, NULL, bgColor);
            button->setAction([this, i, j]()
                              { defaultSlotAction(i, j); });
            UIInventorySlots[i][j] = button;
            slotButtons.push_back(button);

            wholeOffsetX += PADDING + SLOT_SIZE;
        }

        wholeOffsetY += PADDING + SLOT_SIZE;
    }
}

bool Inventory::handleClickEvents()
{
    bool wasActionCalled = false;

    if (!wasActionCalled)
    {
        for (int i = menuButtons.size() - 1; i >= 0; i--)
        {
            if (menuButtons[i]->checkMouseCollision())
            {
                menuButtons[i]->callAction();
                wasActionCalled = true;
                return true;
                break;
            }
        }
    }

    if (!wasActionCalled)
    {
        for (int i = slotButtons.size() - 1; i >= 0; i--)
        {
            if (slotButtons[i]->checkMouseCollision())
            {
                slotButtons[i]->callAction();
                wasActionCalled = true;
                return true;
                break;
            }
        }
    }

    if (!wasActionCalled)
    {
        this->removeMenu();
    }

    return false;
}

bool Inventory::removeMenu()
{
    if (!menu)
    {
        return false;
    }

    delete menu;
    menu = nullptr;
    menuButtons.clear();

    return true;
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

                SDL_Texture *texture = NULL;
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

void Inventory::equipItem(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        return;
    }

    Item *item = items[row][col];

    if (item == nullptr)
    {
        return;
    }

    if (Weapon *weapon = dynamic_cast<Weapon *>(item))
    {

        if (equipedWeapon != nullptr)
        {
            addItem(equipedWeapon);
        }

        equipedWeapon = weapon;
        items[row][col] = nullptr;
    }
    else if (Armor *armor = dynamic_cast<Armor *>(item))
    {

        if (equipedArmor != nullptr)
        {
            addItem(equipedArmor);
        }

        equipedArmor = armor;
        items[row][col] = nullptr;
    }
    else if (Trinket *trinket = dynamic_cast<Trinket *>(item))
    {

        if (equipedTrinket != nullptr)
        {
            addItem(equipedTrinket);
        }

        equipedTrinket = trinket;
        items[row][col] = nullptr;
    }
}

void Inventory::unequipItem(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        return;
    }

    Item *item = items[row][col];

    if (item == nullptr)
    {
        return;
    }

    if (Weapon *weapon = dynamic_cast<Weapon *>(item))
    {
        if (equipedWeapon != nullptr)
        {
            addItem(equipedWeapon);
        }

        equipedWeapon = nullptr;
        items[row][col] = nullptr;
        (void)weapon;
    }
    else if (Armor *armor = dynamic_cast<Armor *>(item))
    {
        if (equipedArmor != nullptr)
        {
            addItem(equipedArmor);
        }

        equipedArmor = nullptr;
        items[row][col] = nullptr;
        (void)armor;
    }
    else if (Trinket *trinket = dynamic_cast<Trinket *>(item))
    {
        if (equipedTrinket != nullptr)
        {
            addItem(equipedTrinket);
        }

        equipedTrinket = nullptr;
        items[row][col] = nullptr;
        (void)trinket;
    }
}

void Inventory::useItem(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        return;
    }

    Item *item = items[row][col];

    if (item == nullptr)
    {
        return;
    }

    if (Weapon *weapon = dynamic_cast<Weapon *>(item))
    {
        if (equipedWeapon == nullptr)
        {
            return;
        }

        //Use Weapon?
        
    }
    else if (Armor *armor = dynamic_cast<Armor *>(item))
    {
        if (equipedArmor == nullptr)
        {
            return;
        }

        //Use Armor?

    }
    else if (Trinket *trinket = dynamic_cast<Trinket *>(item))
    {
        if (equipedArmor == nullptr)
        {
            return;
        }

        //Use Trinket?
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

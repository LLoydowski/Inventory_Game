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

    if (items[row][col] == nullptr)
    {
        return;
    }

    this->removeMenu();

    //? Creating the menu group
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    menu = new UIGroup(mouseX, mouseY);

    //? Defining default button color
    SDL_Color color = {200, 200, 200, 255};

    //? Creating menu background
    UIElement *bg = new UIElement(MENU_BUTTON_WIDTH, 0, 0, 0, color);
    menu->addElement(bg);

    //? Opening the font for menu buttons
    TTF_Font *font = TTF_OpenFont("font/OpenSans.ttf", 24);
    if (font == nullptr)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    int offsetY = 0; //* It defines the relative Y position of next element and the height overall

    //? Creating move button
    UIButton *moveButton = new UIButton(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, "Move", font, rend);
    moveButton->setAction([this, row, col]()
                          { enableMoveMode(row, col); });
    menuButtons.push_back(moveButton);
    menu->addElement(moveButton);
    offsetY += MENU_BUTTON_HEIGHT;

    std::string itemType = items[row][col]->getType();

    //? Handling weapon
    if (itemType == "Weapon")
    {
        Weapon *weapon = dynamic_cast<Weapon *>(items[row][col]);

        if (items[row][col] == equipedWeapon)
        {
            //? Creating equip button
            UIButton *equipButton = new UIButton(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, "Unequip", font, rend);
            equipButton->setAction([this]()
                                   { this->unequipItem(ItemType::Weapon); });
            menuButtons.push_back(equipButton);
            menu->addElement(equipButton);
        }
        else
        {
            //? Creating unequip button
            UIButton *equipButton = new UIButton(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, "Equip", font, rend);
            equipButton->setAction([this, weapon]()
                                   { this->equipItem(weapon); });
            menuButtons.push_back(equipButton);
            menu->addElement(equipButton);
        }

        offsetY += MENU_BUTTON_HEIGHT;
    }

    //? Handling armor
    if (itemType == "Armor")
    {
        Armor *armor = dynamic_cast<Armor *>(items[row][col]);

        if (items[row][col] == equipedArmor)
        {
            //? Creating equip button
            UIButton *equipButton = new UIButton(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, "Unequip", font, rend);
            equipButton->setAction([this]()
                                   { this->unequipItem(ItemType::Armor); });
            menuButtons.push_back(equipButton);
            menu->addElement(equipButton);
        }
        else
        {
            //? Creating unequip button
            UIButton *equipButton = new UIButton(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, "Equip", font, rend);
            equipButton->setAction([this, armor]()
                                   { this->equipItem(armor); });
            menuButtons.push_back(equipButton);
            menu->addElement(equipButton);
        }
        offsetY += MENU_BUTTON_HEIGHT;
    }

    //? Handling trinket
    if (itemType == "Trinket")
    {
        Trinket *trinket = dynamic_cast<Trinket *>(items[row][col]);

        if (items[row][col] == equipedTrinket)
        {
            //? Creating equip button
            UIButton *equipButton = new UIButton(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, "Unequip", font, rend);
            equipButton->setAction([this]()
                                   { this->unequipItem(ItemType::Trinket); });
            menuButtons.push_back(equipButton);
            menu->addElement(equipButton);
        }
        else
        {
            //? Creating unequip button
            UIButton *equipButton = new UIButton(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, "Equip", font, rend);
            equipButton->setAction([this, trinket]()
                                   { this->equipItem(trinket); });
            menuButtons.push_back(equipButton);
            menu->addElement(equipButton);
        }
        offsetY += MENU_BUTTON_HEIGHT;
    }

    //? Checking if the item is equipped, if it isn't creating remove button
    if (
        items[row][col] != this->equipedArmor &&
        items[row][col] != this->equipedWeapon &&
        items[row][col] != this->equipedTrinket)
    {
        //? Creating remove button
        UIButton *removeButton = new UIButton(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, "Remove", font, rend);
        removeButton->setAction([this, row, col]()
                                { removeItem(row, col); });
        menuButtons.push_back(removeButton);
        menu->addElement(removeButton);
        offsetY += MENU_BUTTON_HEIGHT;
    }

    bg->setSize(MENU_BUTTON_WIDTH, offsetY);

    TTF_CloseFont(font);
}

void Inventory::enableMoveMode(int row, int col)
{
    this->isMoveMode = true;
    this->moveOriginRow = row;
    this->moveOriginCol = col;
    this->removeMenu();
}

void Inventory::disableMoveMode()
{
    this->isMoveMode = false;
    this->moveOriginRow = -1;
    this->moveOriginCol = -1;
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
    delete inventoryTitle;
    delete goldText;

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
    inventoryTitle->display(rend);
    goldText->display(rend);

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
    const int height = (rows * (PADDING + SLOT_SIZE)) + PADDING + PADDING_TOP;
    int paddingWhole = PADDING_TOP + PADDING;

    TTF_Font *font = TTF_OpenFont("font/OpenSans.ttf", 18);
    if (font == nullptr)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    inventoryBG = new UIElement(width, height, posX, posY, inventoryBGColor);
    inventoryTitle = new UIElement(100, paddingWhole, posX + PADDING, posY, inventoryBGColor, inventoryName, font, rend);
    goldText = new UIElement(110, paddingWhole, (posX + width) - 110 - PADDING, posY, inventoryBGColor, "Gold: --TEST--", font, rend);

    int wholeOffsetY = posY + PADDING + PADDING_TOP;
    for (int i = 0; i < rows; i++)
    {
        int wholeOffsetX = posX + PADDING;
        for (int j = 0; j < cols; j++)
        {
            SDL_Color bgColor = {153, 154, 158, SDL_ALPHA_OPAQUE};
            UIButtonImage *button = new UIButtonImage(SLOT_SIZE, SLOT_SIZE, wholeOffsetX, wholeOffsetY, NULL, bgColor);

            if (items[i][j])
            {
                button->setTexture(items[i][j]->getTexture());
            }

            button->setAction([this, i, j]()
                              { defaultSlotAction(i, j); });
            UIInventorySlots[i][j] = button;
            slotButtons.push_back(button);

            wholeOffsetX += PADDING + SLOT_SIZE;
        }

        wholeOffsetY += PADDING + SLOT_SIZE;
    }

    isUIGenerated = true;
}

bool Inventory::handleClickEvents()
{
    if (this->isMoveMode)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (UIInventorySlots[i][j]->checkMouseCollision())
                {
                    this->moveItems(moveOriginRow, moveOriginCol, i, j);
                    this->isMoveMode = false;
                    this->moveOriginCol = -1;
                    this->moveOriginRow = -1;
                    this->generateUIElements();

                    return true;
                    break;
                }
            }
        }
    }

    for (int i = menuButtons.size() - 1; i >= 0; i--)
    {
        if (menuButtons[i]->checkMouseCollision())
        {
            menuButtons[i]->callAction();
            return true;
            break;
        }
    }

    for (int i = slotButtons.size() - 1; i >= 0; i--)
    {
        if (slotButtons[i]->checkMouseCollision())
        {
            slotButtons[i]->callAction();
            return true;
            break;
        }
    }

    this->removeMenu();
    this->disableMoveMode();

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
    this->generateUIElements();
    this->removeMenu();
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

void Inventory::equipItem(Weapon *weapon)
{
    equipedWeapon = weapon;
    this->removeMenu();
}
void Inventory::equipItem(Armor *armor)
{
    equipedArmor = armor;
    this->removeMenu();
}
void Inventory::equipItem(Trinket *trinket)
{
    equipedTrinket = trinket;
    this->removeMenu();
}

void Inventory::unequipItem(ItemType parameter)
{
    switch (parameter)
    {
    case ItemType::Weapon:
        equipedWeapon = nullptr;
        break;
    case ItemType::Armor:
        equipedArmor = nullptr;
        break;
    case ItemType::Trinket:
        equipedTrinket = nullptr;
        break;
    }

    this->generateUIElements();
    this->removeMenu();
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

    // Using potion code
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

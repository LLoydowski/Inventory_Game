#include <SDL2/SDL.h>

#include <Inventory.hpp>
#include <UIElement.hpp>
#include <UIButton.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <vector>

Inventory::Inventory(int rows, int cols) : rows{rows}, cols{cols}, equipedArmor{nullptr}, equipedWeapon{nullptr}, equipedTrinket{nullptr}
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

    windowWidth = -1;
    windowHeight = -1;
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
    for (int i = 0; i < rows * cols; i++)
    {
        delete UIInventorySlots[i];
    }
    delete[] UIInventorySlots;
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
    if (windowHeight == -1 || windowHeight == -1)
    {
        std::cout << "You need to set width and height first ( setWindowParams(width, height); )" << std::endl;
        return;
    }

    inventoryBG->display(rend);

    for (int i = 0; i < rows * cols; i++)
    {
        if (UIInventorySlots[i] != nullptr)
        {
            UIInventorySlots[i]->display(rend);
        }
    }
}
void Inventory::generateUIElements()
{
    const SDL_Color inventoryBGColor = {116, 117, 125, SDL_ALPHA_OPAQUE};

    const int width = (cols * (PADDING + SLOT_SIZE)) + PADDING;
    const int height = (rows * (PADDING + SLOT_SIZE)) + PADDING;

    const int bgPosX = (windowWidth / 2) - (width / 2);
    const int bgPosY = (windowHeight / 2) - (height / 2);

    inventoryBG = new UIElement(width, height, bgPosX, bgPosY, inventoryBGColor);

    UIInventorySlots = new UIElement *[rows * cols];
    SDL_Color slotColor = {149, 150, 163, SDL_ALPHA_OPAQUE};

    int wholeOffsetY = inventoryBG->getY() + PADDING;
    int iterationCounter = 0;
    for (int row = 0; row < rows; row++)
    {
        int wholeOffsetX = inventoryBG->getX() + PADDING;
        for (int col = 0; col < cols; col++)
        {
            UIInventorySlots[iterationCounter] = new UIElement(SLOT_SIZE, SLOT_SIZE, wholeOffsetX, wholeOffsetY, slotColor);

            iterationCounter += 1;
            wholeOffsetX += PADDING + SLOT_SIZE;
        }
        wholeOffsetY += PADDING + SLOT_SIZE;
    }
}

bool Inventory::addItem(Item *item)
{
    int interationCounter = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (items[i][j] == nullptr)
            {
                TTF_Font *font = TTF_OpenFont("font/OpenSans.ttf", 24);
                items[i][j] = item;
                std::string itemName = item->getName();

                char firstLetter = itemName[0];
                std::string text = "";
                text.push_back(firstLetter);

                UIInventorySlots[interationCounter]->setText(text, font, rend);

                return true;
                TTF_CloseFont(font);
            }

            interationCounter++;
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

    if(oldRow < 0 || oldRow > rows || newRow < 0 || newRow > rows || oldCol < 0 || oldCol > cols || newCol < 0 || newCol > cols) {
        return false;
    }

    Item* tempItem = items[oldRow][oldCol];
    items[oldRow][oldCol] = items[newRow][newCol];
    items[newRow][newCol] = tempItem;
    return true;
}


void Inventory::sortItems(char parameter)
{
    std::vector<Item*> itemList;

    for(int i = 0; i < rows; i ++) {
        for(int j = 0; j < cols; j ++) {
            if(items[i][j] != nullptr) {
                itemList.push_back(items[i][j]);
            }
        }
    }

    int n = itemList.size();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool shouldSwap = false;

            if (parameter == 'p') {
                shouldSwap = itemList[j]->getPrice() > itemList[j + 1]->getPrice();
            }
            else if (parameter == 'n') {
                shouldSwap = itemList[j]->getName() > itemList[j + 1]->getName();
            }
            else if (parameter == 'r') {
                shouldSwap = itemList[j]->getRarity() > itemList[j + 1]->getRarity();
            }
            else if (parameter == 'f') {
                shouldSwap = !itemList[j]->getFavourite() && itemList[j + 1]->getFavourite();
            }

            if (shouldSwap) {
                std::swap(itemList[j], itemList[j + 1]);
            }
        }
    }
    
}

bool Inventory::toggleFavourite(int row, int col)
{      
    if (dynamic_cast<Item*>(items[col][row]) == nullptr) {
        return false;
    }

    if(items[row][col]->getFavourite()) {
        items[row][col]->setFavourite(true);
    } else {
        items[row][col]->setFavourite(false);
    }
    return true;
}

void Inventory::equipItem(int row, int col)
{
    
}


int Inventory::getCols()
{
    return cols;
}

int Inventory::getRows()
{
    return rows;
}

void Inventory::setWindowParams(int windowWidth, int windowHeight, SDL_Renderer *rend)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->rend = rend;
    generateUIElements();
}

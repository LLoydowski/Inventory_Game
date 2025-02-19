#include <SDL2/SDL.h>

#include <Inventory.hpp>
#include <UIElement.hpp>
#include <UIButton.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Inventory::Inventory(int rows, int cols, int windowWidth, int windowHeight, SDL_Renderer *rend) : rows{rows}, cols{cols}, rend{rend}
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

    // Generating UI objects
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
void Inventory::displaySDL()
{
    inventoryBG->display(rend);

    for (int i = 0; i < rows * cols; i++)
    {
        if (UIInventorySlots[i] != nullptr)
        {
            UIInventorySlots[i]->display(rend);
        }
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

int Inventory::getCols()
{
    return cols;
}

int Inventory::getRows()
{
    return rows;
}
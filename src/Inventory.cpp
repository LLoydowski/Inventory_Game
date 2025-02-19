#include <SDL2/SDL.h>

#include <Inventory.hpp>
#include <UIElement.hpp>

Inventory::Inventory(int rows, int cols) : rows{rows}, cols{cols}
{
    items = new Item **[rows];

    for (int i = 0; i < rows; i++)
    {
        items[i] = new Item *[cols];
        for (int j = 0; j < cols; j++)
        {
            items[i][j] = nullptr;
        }
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

void Inventory::displaySDL(SDL_Renderer *rend, int windowWidth, int windowHeight)
{
    const SDL_Color inventoryBGColor = {116, 117, 125, SDL_ALPHA_OPAQUE};

    const int PADDING = 25;
    const int SLOT_SIZE = 50;

    const int width = (cols * (PADDING + SLOT_SIZE)) + PADDING;
    const int height = (rows * (PADDING + SLOT_SIZE)) + PADDING;

    const int bgPosX = (windowWidth / 2) - (width / 2);
    const int bgPosY = (windowHeight / 2) - (height / 2);

    UIElement inventoryBG(width, height, bgPosX, bgPosY, inventoryBGColor);

    inventoryBG.display(rend);

    SDL_SetRenderDrawColor(rend, 149, 150, 163, SDL_ALPHA_OPAQUE);
    int wholeOffsetY = bgPosY + PADDING;
    for (int row = 0; row < rows; row++)
    {
        int wholeOffsetX = bgPosX + PADDING;
        for (int col = 0; col < cols; col++)
        {
            SDL_Rect _rect = {wholeOffsetX, wholeOffsetY, SLOT_SIZE, SLOT_SIZE};
            SDL_RenderFillRect(rend, &_rect);

            wholeOffsetX += PADDING + SLOT_SIZE;
        }
        wholeOffsetY += PADDING + SLOT_SIZE;
    }
}

bool Inventory::addItem(Item *item)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (items[i][j] == nullptr)
            {
                items[i][j] = item;
                return true;
            }
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
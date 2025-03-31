#include "Shop.hpp"
#include "Player.hpp"
#include "Item.hpp"

Shop::Shop(int rows, int cols) : Inventory(rows, cols)
{
}

bool Shop::buyItem(int col, int row, Player *player)
{
    Item *item = items[col][row];

    if (player->getGold() < item->getPrice())
    {
        return false;
    }

    if (!player->hasFreeSlot())
    {
        return false;
    }

    player->addItemToInv(item);
    return true;
}
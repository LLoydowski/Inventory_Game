#include <string>

#include <Player.hpp>

Player::Player() : name{"Guest"}, HP{100}, gold{10}
{
    inventory = new Inventory(INVENTORY_ROWS, INVENTORY_COLS);
}
Player::Player(std::string name, float HP, float gold) : name{name}, HP{HP}, gold{gold}
{
    inventory = new Inventory(INVENTORY_ROWS, INVENTORY_COLS);
}
Player::~Player()
{
    delete inventory;
}

int Player::getGold()
{
    return gold;
}

Inventory *Player::getInv()
{
    return inventory;
}

bool Player::hasFreeSlot()
{
    return inventory->hasFreeSlot();
}

void Player::addItemToInv(Item *item)
{
    if (inventory->hasFreeSlot())
    {
        inventory->addItem(item);
    }
}

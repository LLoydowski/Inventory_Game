#include <string>

#include <Player.hpp>

Player::Player() : name{"Guest"}
{
    inventory = new Inventory(INVENTORY_ROWS, INVENTORY_COLS);
}
Player::Player(std::string name, float maxHP, float gold) : name{name}
{
    inventory = new Inventory(INVENTORY_ROWS, INVENTORY_COLS);
    inventory->setMaxHP(maxHP);
    inventory->setHP(maxHP);
    inventory->setGold(gold);
}
Player::~Player()
{
    delete inventory;
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

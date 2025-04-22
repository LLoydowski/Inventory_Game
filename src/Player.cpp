#include <string>

#include <Player.hpp>

Player::Player() : name{"Guest"}
{
    inventory = new Inventory(INVENTORY_ROWS, INVENTORY_COLS);
}
Player::Player(std::string name, float maxHP, float gold) : name{name}
{
    inventory = new Inventory(INVENTORY_ROWS, INVENTORY_COLS);
    inventory->setHP(maxHP);
    inventory->setTempHP(maxHP);
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

void Player::goToArena()
{
    this->pos = PlayerPosition::Arena;
}

void Player::goToLobby()
{
    this->pos = PlayerPosition::Lobby;
}

void Player::setTier(int tier)
{
    this->tier = tier;
}

void Player::setLvl(int lvl)
{
    this->lvl = lvl;
}

PlayerPosition Player::getPlayerPosition()
{
    return pos;
}

int Player::getTier()
{
    return tier;
}

int Player::getLvl()
{
    return lvl;
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

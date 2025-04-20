#pragma once

#include <string>
#include <Inventory.hpp>

class Player
{
private:
    const int INVENTORY_ROWS = 3;
    const int INVENTORY_COLS = 4;

    std::string name;
    Inventory *inventory;

public:
    Player();
    Player(std::string name, float HP, float gold);
    ~Player();

    bool hasFreeSlot();
    void addItemToInv(Item *item);

    //? Getters
    Inventory *getInv();
};
#pragma once

#include <string>
#include <Inventory.hpp>
#include <Enums.hpp>

class Player
{
private:
    const int INVENTORY_ROWS = 3;
    const int INVENTORY_COLS = 4;

    int tier = 1;
    int lvl = 1;

    std::string name;
    Inventory *inventory;
    PlayerPosition pos = PlayerPosition::Lobby;

public:
    Player();
    Player(std::string name, float HP, float gold);
    ~Player();

    bool hasFreeSlot();
    void addItemToInv(Item *item);

    //? Getters
    Inventory *getInv();
    PlayerPosition getPlayerPosition();
    int getTier();
    int getLvl();

    //? Setters
    void goToArena();
    void goToLobby();
    void setTier(int tier);
    void setLvl(int lvl);
};
#include <Inventory.hpp>
#include <Player.hpp>

class Shop : public Inventory
{

public:
    Shop(int rows, int cols);
    bool buyItem(int col, int row, Player *player);
};
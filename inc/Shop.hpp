#include <Inventory.hpp>
#include <Player.hpp>

class Shop : public Inventory
{
private:
    void defaultSlotAction(int row, int col) override;

public:
    Shop(int rows, int cols);

    bool buyItem(int col, int row, Player *player);
    bool handleClickEvents() override;
};
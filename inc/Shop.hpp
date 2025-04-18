#include <Inventory.hpp>
#include <Player.hpp>

class Shop : public Inventory
{
private:
    void defaultSlotAction(int row, int col) override;

    const int MENU_BUTTON_WIDTH = 100;
    const int MENU_BUTTON_HEIGHT = 40;

public:
    Shop(int rows, int cols);

    bool buyItem(int col, int row, Player *player);
    bool handleClickEvents() override;
    void displaySDL(SDL_Renderer *rend) override;
};
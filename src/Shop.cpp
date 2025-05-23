#include "Shop.hpp"
#include "Player.hpp"
#include "Item.hpp"

#include <iomanip>
#include <sstream>

void Shop::defaultSlotAction(int row, int col)
{
    if (items[row][col] == nullptr)
    {
        return;
    }

    this->removeMenu();

    //? Creating the menu group
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    menu = new UIGroup(mouseX, mouseY);

    //? Defining default button color
    SDL_Color color = {200, 200, 200, 255};

    //? Creating menu background
    UIElement *bg = new UIElement(MENU_BUTTON_WIDTH, 0, 0, 0, color);
    menu->addElement(bg);

    //? Opening the font for menu buttons
    TTF_Font *font = TTF_OpenFont("font/OpenSans.ttf", 42);
    if (font == nullptr)
    {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return;
    }

    int offsetY = 0; //* It defines the relative Y position of next element and the height overall
    int width = 0;

    UIElement *itemName = new UIElement(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, items[row][col]->getName(), font, rend);
    menu->addElement(itemName);
    offsetY += MENU_BUTTON_HEIGHT;
    calculateMenuElementDimentions(width, itemName->getTextTexture());

    if (playerUsingShop->getTier() >= items[row][col]->getTier())
    {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << items[row][col]->getPrice();
        std::string priceString = stream.str();
        std::string buyButtonText = "Buy (" + priceString + ")";
        UIButton *buyButton = new UIButton(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, buyButtonText, font, rend);
        buyButton->setAction([this, row, col]()
                             { this->buyItem(row, col); });
        menuButtons.push_back(buyButton);
        menu->addElement(buyButton);
        offsetY += MENU_BUTTON_HEIGHT;
        calculateMenuElementDimentions(width, buyButton->getTextTexture());
    }
    else
    {
        UIElement *cantBuy = new UIElement(MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT, 0, offsetY, color, "You can't buy this yet", font, rend);
        menu->addElement(cantBuy);
        offsetY += MENU_BUTTON_HEIGHT;
        calculateMenuElementDimentions(width, cantBuy->getTextTexture());
    }

    // ItemType itemType = items[row][col]->getType();

    bg->setSize(MENU_BUTTON_WIDTH, offsetY);
    menu->resizeElementsWidth(width + MENU_PADDING_RIGHT);

    if (width + mouseX >= windowWidth)
    {
        menu->setPos(mouseX - width, mouseY);
    }

    TTF_CloseFont(font);
}

Shop::Shop(int rows, int cols) : Inventory(rows, cols)
{
    this->inventoryName = "Shop";
}

bool Shop::buyItem(int col, int row)
{
    if (playerUsingShop == nullptr)
    {
        std::cout << "[Shop/buyItem] ERROR: No player uses the shop\n";
        return false;
    }

    Item *item = items[col][row];

    Inventory *inv = playerUsingShop->getInv();

    if (inv->getGold() < item->getPrice())
    {
        return false;
    }

    if (!playerUsingShop->hasFreeSlot())
    {
        return false;
    }

    Item *itemSold = item->copy();

    inv->setGold(inv->getGold() - item->getPrice());

    playerUsingShop->addItemToInv(itemSold);
    this->removeMenu();

    inv->generateUIElements();

    return true;
}

bool Shop::handleClickEvents()
{
    for (int i = menuButtons.size() - 1; i >= 0; i--)
    {
        if (menuButtons[i]->checkMouseCollision())
        {
            menuButtons[i]->callAction();
            return true;
            break;
        }
    }

    for (int i = slotButtons.size() - 1; i >= 0; i--)
    {
        if (slotButtons[i]->checkMouseCollision())
        {
            slotButtons[i]->callAction();
            return true;
            break;
        }
    }

    this->removeMenu();
    this->disableMoveMode();

    return false;
}

void Shop::displaySDL(SDL_Renderer *rend)
{
    if (posX == -1 || posY == -1)
    {
        std::cout << "You need to set position first ( setPos(posX, posY); )" << std::endl;
        return;
    }

    inventoryBG->display(rend);
    inventoryTitle->display(rend);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (UIInventorySlots[i][j] != nullptr)
            {
                UIInventorySlots[i][j]->display(rend, PADDING);
            }
        }
    }

    if (menu != nullptr)
    {
        menu->display(rend);
    }
}

void Shop::setPlayerUsingShop(Player *plr)
{
    this->playerUsingShop = plr;
}

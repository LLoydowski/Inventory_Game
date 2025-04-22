#include "Arena.hpp"
#include <UIGroup.hpp>
#include <SDL2/SDL_ttf.h>
#include <Inventory.hpp>

#include <sstream>
#include <iomanip>

void Arena::enableAttackMode()
{
    isInAttackMode = true;
    attackButton->disable();

    fightBar = new FightBar(20, windowHeight - 70, windowWidth - 40, 50);
}

Arena::Arena()
    : player{nullptr}, enemy{nullptr}, lvl{0}, tier{1}
{
}

Arena::Arena(Player *player)
    : player{player}, enemy{nullptr}, lvl{0}, tier{1}
{
}

Arena::~Arena()
{
    delete enemy;
    delete enemyInfo;
    delete attackButton;
    delete lvlText;

    if (fightBar != nullptr)
    {
        delete fightBar;
    }
}

void Arena::nextFight()
{
    if (lvl == 4)
    {
        lvl = 0;
        tier++;
        generateEnemy();
        return;
    }

    lvl++;
    generateEnemy();

    std::string text = "LVL: " + std::to_string(lvl);
    text += " / TIER: " + std::to_string(tier);

    lvlText->setText(text, font, rend);
}

void Arena::generateEnemy()
{
    float HP = enemyTiers[tier].HP + (enemyTiers[tier].bHP * lvl);
    float DMG = enemyTiers[tier].DMG + (enemyTiers[tier].bDMG * lvl);
    float DEF = enemyTiers[tier].DEF + (enemyTiers[tier].bDEF * lvl);

    enemy = new Enemy("Skibidi", HP, DMG, DEF);

    if (enemyInfo != nullptr)
    {
        std::stringstream stream;

        //? Setting enemy name in enemy info
        enemyInfo->getElement(1)->setText(enemy->getName(), font, rend);

        //? Setting enemy HP in enemy info
        stream.str("");
        stream.clear();
        stream << std::fixed << std::setprecision(1) << enemy->getTempHP();
        std::string tempHPString = stream.str();

        stream.str("");
        stream.clear();
        stream << std::fixed << std::setprecision(1) << enemy->getHP();
        std::string HPString = stream.str();

        std::string HPtext = "HP: " + tempHPString + " / " + HPString;

        enemyInfo->getElement(2)->setText(HPtext, font, rend);

        //? Setting enemy DMG in enemy info
        stream.str("");
        stream.clear();
        stream << std::fixed << std::setprecision(1) << enemy->getDMG();
        std::string DMGString = stream.str();

        std::string DMGText = "DMG: " + DMGString;

        enemyInfo->getElement(3)->setText(DMGText, font, rend);

        //? Setting enemy DEF in enemy info
        stream.str("");
        stream.clear();
        stream << std::fixed << std::setprecision(1) << enemy->getDEF();
        std::string DEFString = stream.str();

        std::string DEFText = "DEF: " + DEFString;

        enemyInfo->getElement(4)->setText(DEFText, font, rend);
    }

    if (rend != nullptr)
    {
        enemy->setPos(windowWidth / 2, windowHeight / 2);
        enemy->setTexture(loadedTextures["placeholder"]);
    }
}

void Arena::display()
{
    if (enemy != nullptr)
    {
        enemy->display(rend);
    }
    if (lvlText != nullptr)
    {
        lvlText->display(rend);
    }

    if (!isInAttackMode)
    {
        if (enemyInfo != nullptr)
        {
            enemyInfo->display(rend);
        }
        if (attackButton != nullptr)
        {
            attackButton->display(rend);
        }
    }
    else
    {
        fightBar->display(rend);
    }
}

bool Arena::handleKeyboardEvents(SDL_Event event)
{
    if (isInAttackMode)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            float hitMultiplier = fightBar->hit();

            Inventory *inv = player->getInv();
            Weapon *playerWeapon = inv->getWeapon();

            if (playerWeapon == nullptr)
            {
                std::cout << "[Arena/handleKeyboardEvents] The weapon is missing.\n";
                return false;
            }

            float playerDMG = playerWeapon->getDamage();

            float DMGDone = playerDMG * hitMultiplier;

            enemy->dealDMG(DMGDone);

            std::stringstream stream;

            stream.str("");
            stream.clear();
            stream << std::fixed << std::setprecision(1) << enemy->getTempHP();
            std::string tempHPString = stream.str();

            stream.str("");
            stream.clear();
            stream << std::fixed << std::setprecision(1) << enemy->getHP();
            std::string HPString = stream.str();

            std::string HPtext = "HP: " + tempHPString + " / " + HPString;

            enemyInfo->getElement(2)->setText(HPtext, font, rend);

            isInAttackMode = false;
            attackButton->enable();

            delete fightBar;
            fightBar = nullptr;

            if (enemy->getTempHP() <= 0)
            {
                player->goToLobby();
            }

            return true;
        }
    }
    return false;
}

bool Arena::handleClickEvents()
{
    if (attackButton->checkMouseCollision())
    {
        attackButton->callAction();
        return true;
    }

    return false;
}

Enemy *Arena::getEnemy()
{
    return enemy;
}

Player *Arena::getPlayer()
{
    return player;
}

void Arena::setPlayer(Player *player)
{
    this->player = player;
}

void Arena::setEnemy(Enemy *enemy)
{
    this->enemy = enemy;
}

void Arena::calibrateWindowPos(int windowWidth, int windowHeight, SDL_Renderer *rend, TTF_Font *font)
{
    this->rend = rend;
    this->enemyInfo = new UIGroup(windowWidth - 270, windowHeight - 150);
    this->font = font;

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    SDL_Color color = {200, 200, 200, 255};

    int offsetY = 0;

    UIElement *background = new UIElement(250, 130, 0, 0, color, " ", font, rend);
    this->enemyInfo->addElement(background);

    UIElement *enemyName = new UIElement(250, 30, 0, offsetY, color, "Test", font, rend);
    this->enemyInfo->addElement(enemyName);
    offsetY += 30;

    UIElement *enemyHP = new UIElement(250, 30, 0, offsetY, color, "HP: X/Y", font, rend);
    this->enemyInfo->addElement(enemyHP);
    offsetY += 30;

    UIElement *enemyDMG = new UIElement(250, 30, 0, offsetY, color, "DMG: X", font, rend);
    this->enemyInfo->addElement(enemyDMG);
    offsetY += 30;

    UIElement *enemyDEF = new UIElement(250, 30, 0, offsetY, color, "DEF: X", font, rend);
    this->enemyInfo->addElement(enemyDEF);
    offsetY += 30;

    this->attackButton = new UIButton(130, 50, 20, windowHeight - 70, color, "Attack", font, rend);
    attackButton->setAction([this]()
                            { this->enableAttackMode(); });

    this->lvlText = new UIElement(250, 40, 20, 20, color, "LVL: 1 / TIER: 1", font, rend);
}

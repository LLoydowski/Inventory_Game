#include "Arena.hpp"
#include <UIGroup.hpp>
#include <SDL2/SDL_ttf.h>

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
}

void Arena::nextFight()
{
    if (lvl != 5)
    {
        lvl = 0;
        tier++;
        generateEnemy();
        return;
    }

    lvl++;
    generateEnemy();
}

void Arena::generateEnemy()
{
    float HP = enemyTiers[tier].HP + (enemyTiers[tier].bHP * lvl);
    float DMG = enemyTiers[tier].DMG + (enemyTiers[tier].bDMG * lvl);
    float DEF = enemyTiers[tier].DEF + (enemyTiers[tier].bDEF * lvl);

    enemy = new Enemy("Zombie", HP, DMG, DEF);

    if (enemyInfo != nullptr)
    {
        enemyInfo->getElement(1)->setText(enemy->getName(), font, rend);
    }
}

void Arena::display()
{
    if (enemyInfo != nullptr)
    {
        enemyInfo->display(rend);
    }
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

    SDL_Color color = {200, 200, 200, 255};

    UIElement *background = new UIElement(250, 130, 0, 0, color, " ", font, rend);
    this->enemyInfo->addElement(background);

    UIElement *enemyName = new UIElement(250, 30, 0, 0, color, "Test", font, rend);
    this->enemyInfo->addElement(enemyName);
}

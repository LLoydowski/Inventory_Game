#pragma once

#include <Player.hpp>
#include <Enemy.hpp>
#include <UIGroup.hpp>
#include <FightBar.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Arena
{
private:
    Player *player = nullptr;
    Enemy *enemy = nullptr;

    int lvl, tier;
    bool isInAttackMode = false;
    bool lost = false;

    int windowWidth, windowHeight;

    SDL_Renderer *rend = nullptr;
    TTF_Font *font = nullptr;

    UIGroup *enemyInfo = nullptr;
    UIButton *attackButton = nullptr;
    UIElement *lvlText = nullptr;
    UIElement *HPDisplay = nullptr;
    FightBar *fightBar = nullptr;

    UIElement *lostText = nullptr;
    UIButton *restartButton = nullptr;

    void
    enableAttackMode();

public:
    Arena();
    Arena(Player *player);
    ~Arena();

    void nextFight();
    void generateEnemy();
    void display();
    bool handleClickEvents();
    bool handleKeyboardEvents(SDL_Event event);

    //? Getters
    Enemy *getEnemy();
    Player *getPlayer();

    //? Setters
    void setPlayer(Player *player);
    void setEnemy(Enemy *enemy);
    void calibrateWindowPos(int windowWidth, int windowHeight, SDL_Renderer *rend, TTF_Font *font);
};
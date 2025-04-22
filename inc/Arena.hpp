#pragma once

#include <Player.hpp>
#include <Enemy.hpp>
#include <UIGroup.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Arena
{
private:
    Player *player = nullptr;
    Enemy *enemy = nullptr;

    int lvl, tier;

    int windowWidth, windowHeight;

    UIGroup *enemyInfo = nullptr;
    SDL_Renderer *rend = nullptr;
    TTF_Font *font = nullptr;

    UIButton *attackButton = nullptr;

public:
    Arena();
    Arena(Player *player);
    ~Arena();

    void nextFight();
    void generateEnemy();
    void display();

    //? Getters
    Enemy *getEnemy();
    Player *getPlayer();

    //? Setters
    void setPlayer(Player *player);
    void setEnemy(Enemy *enemy);
    void calibrateWindowPos(int windowWidth, int windowHeight, SDL_Renderer *rend, TTF_Font *font);
};
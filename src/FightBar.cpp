#include "FightBar.hpp"

#include <UIElement.hpp>
#include <Enums.hpp>

#include <iostream>

void FightBar::updateCrosshair()
{
    if (crossDirection == Direction::Right)
    {
        crosshair->setX(crosshair->getX() + crossSpeed);
    }
    else if (crossDirection == Direction::Left)
    {
        crosshair->setX(crosshair->getX() - crossSpeed);
    }

    if (crosshair->getX() >= this->width + this->posX)
    {
        crossDirection = Direction::Left;
    }
    if (crosshair->getX() <= this->posX)
    {
        crossDirection = Direction::Right;
    }
}

FightBar::FightBar(int posX, int posY, int width, int height)
    : posX{posX}, posY{posY}, width{width}, height{height}
{
    crossX = posX;
    background = new UIElement(width, height, posX, posY, {50, 50, 50, 1});
    crosshair = new UIElement(crossWidth, height, crossX - crossWidth / 2, posY, {255, 255, 255, 1});
    center = new UIElement(centerHitBox * 2, height, posX + width / 2 - centerHitBox, posY, {100, 100, 100, 1});
}

FightBar::~FightBar()
{
    if (background != nullptr)
    {
        delete background;
    }
    if (crosshair != nullptr)
    {
        delete crosshair;
    }
    if (center != nullptr)
    {
        delete center;
    }
}

void FightBar::display(SDL_Renderer *rend)
{
    background->display(rend);
    center->display(rend);
    crosshair->display(rend);
    this->updateCrosshair();
}

void FightBar::hit()
{
    int center = posX + width / 2;

    std::cout << "[FightBar] Center (+/- 5): " << center << "\n";
    std::cout << "[FightBar] Crosshair (+/- 5): " << crosshair->getX() << "\n";

    bool leftConstrain = crosshair->getX() >= center - centerHitBox;
    bool rightConstrain = crosshair->getX() <= center + centerHitBox;

    if (leftConstrain && rightConstrain)
    {
        std::cout << "[FightBar/hit] STATUS: HIT\n";
    }
    else
    {
        std::cout << "[FightBar/hit] STATUS: HITn't\n";
    }
}

void FightBar::setSpeed(int speed)
{
    this->crossSpeed = speed;
}

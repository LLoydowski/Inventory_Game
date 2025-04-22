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
    mild = new UIElement(mildHitBox * 2, height, posX + width / 2 - mildHitBox, posY, {70, 70, 70, 1});
    center = new UIElement(centerHitBox * 2, height, posX + width / 2 - centerHitBox, posY, {130, 130, 130, 1});
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
    if (mild != nullptr)
    {
        delete mild;
    }
}

void FightBar::display(SDL_Renderer *rend)
{
    background->display(rend);
    mild->display(rend);
    center->display(rend);
    crosshair->display(rend);
    if (!wasHit)
    {
        this->updateCrosshair();
    }
}

float FightBar::hit()
{
    wasHit = true;

    int center = posX + width / 2;

    // std::cout << "[FightBar] Center (+/- 5): " << center << "\n";
    // std::cout << "[FightBar] Crosshair (+/- 5): " << crosshair->getX() << "\n";

    bool centerLeftConstrain = crosshair->getX() >= center - centerHitBox;
    bool centerRightConstrain = crosshair->getX() <= center + centerHitBox;

    bool mildLeftConstrain = crosshair->getX() >= center - mildHitBox;
    bool mildRightConstrain = crosshair->getX() <= center + mildHitBox;

    if (centerLeftConstrain && centerRightConstrain)
    {
        // std::cout << "[FightBar/hit] STATUS: HIT\n";
        return CENTER_HIT;
    }
    else if (mildLeftConstrain && mildRightConstrain)
    {
        // std::cout << "[FightBar/hit] STATUS: kinda HIT\n";
        return MILD_HIT;
    }
    else
    {
        // std::cout << "[FightBar/hit] STATUS: HITn't\n";
        return BAD_HIT;
    }
}

void FightBar::setSpeed(int speed)
{
    this->crossSpeed = speed;
}

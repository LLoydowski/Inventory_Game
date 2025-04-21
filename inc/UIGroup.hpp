#pragma once

#include <UIElement.hpp>

#include <vector>

class UIGroup
{
private:
    std::vector<UIElement *> elements;
    int posX, posY;

public:
    UIGroup();
    UIGroup(int posX, int posY);
    ~UIGroup();
    void addElement(UIElement *element);
    void display(SDL_Renderer *rend);
    void setPos(int x, int y);
    void resizeElementsWidth(int width);

    UIElement *getElement(int index);
};
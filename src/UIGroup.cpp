#include "UIGroup.hpp"

UIGroup::UIGroup() : posX{0}, posY{0}
{
}

UIGroup::UIGroup(int posX, int posY) : posX{posX}, posY{posY}
{
}
UIGroup::~UIGroup()
{
    for (UIElement *element : elements)
    {
        delete element;
    }
};
void UIGroup::addElement(UIElement *element)
{
    element->setParentPos(posX, posY);
    elements.push_back(element);
}

void UIGroup::display(SDL_Renderer *rend)
{
    for (UIElement *element : elements)
    {
        element->display(rend);
    }
}

void UIGroup::setPos(int x, int y)
{
    this->posX = x;
    this->posY = y;

    for (UIElement *element : elements)
    {
        element->setParentPos(posX, posY);
    }
}

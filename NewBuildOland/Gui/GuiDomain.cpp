#include "GuiDomain.h"

GuiDomain::GuiDomain() {}

bool GuiDomain::handleEvent(sf::Event e)
{
    for (auto i = layers.begin(); i != layers.end(); i++)
        if ((*i)->handleEvent(e))
            return true;
    return false;
}

void GuiDomain::draw(sf::RenderWindow& rw)
{
    for (auto i = layers.begin(); i != layers.end(); i++)
        (*i)->draw(rw);
}

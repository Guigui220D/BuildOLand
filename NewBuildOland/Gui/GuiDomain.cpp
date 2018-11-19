#include "GuiDomain.h"

GuiDomain::GuiDomain() {}

bool GuiDomain::handleEvent(sf::Event e, sf::RenderWindow& rw)
{
    for (auto i = zones.begin(); i != zones.end(); i++)
        if ((*i)->handleEvent(e, rw))
            return true;
    return false;
}

void GuiDomain::draw(sf::RenderWindow& rw)
{
    for (auto i = zones.begin(); i != zones.end(); i++)
        (*i)->draw(rw);
}

void GuiDomain::update(float dt, sf::RenderWindow& rw)
{
    for (auto i = zones.begin(); i != zones.end(); i++)
        (*i)->update(dt, rw);
}

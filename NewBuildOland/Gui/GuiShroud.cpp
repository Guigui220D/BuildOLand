#include "GuiShroud.h"
#include <iostream>

GuiShroud::GuiShroud(sf::Color color) :
    GuiZone(sf::FloatRect(0.f, 0.f, 10.f, 10.f), 1.f, ZoneHAlign::HLeft, ZoneVAlign::VTop)
{
    setZoneWidth(1.f);
    shroud.setSize(sf::Vector2f(1.f, 1.f));
    shroud.setFillColor(color);
}

bool GuiShroud::handleEvent(sf::Event e, sf::RenderWindow& rw)
{
    //The shroud doesn't let events pass
    return enabled;
}

void GuiShroud::draw(sf::RenderWindow& rw)
{
    if (enabled)
    {
        rw.setView(getView(rw.getSize()));
        rw.draw(shroud);
    }
}

void GuiShroud::update(float dt, sf::RenderWindow& rw)
{
}

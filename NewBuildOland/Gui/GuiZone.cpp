#include "GuiZone.h"

GuiZone::GuiZone(sf::FloatRect zone, float aspectRatio, ZoneHAlign hAlign, ZoneVAlign vAlign) :
    rect(zone),
    ratio(aspectRatio),
    hAlign(hAlign),
    vAlign(vAlign),
    viewWindowSize()
{ }

bool GuiZone::handleEvent(sf::Event e)
{

}

void GuiZone::draw(sf::RenderWindow& rw)
{

}

sf::View GuiZone::getView(sf::Vector2f windowSize)
{
    if (windowSize != viewWindowSize)
    {
        viewWindowSize = windowSize;
        calculateView();
    }
    return calculatedView;
}

void GuiZone::calculateView()
{
    sf::View ret(sf::FloatRect(0, 0, ratio, 1));
    sf::FloatRect zoneRect(rect.left * viewWindowSize.x, rect.top * viewWindowSize.y, rect.width * viewWindowSize.x, rect.height * viewWindowSize.y);
    float zoneRatio = zoneRect.width / zoneRect.height;
    if (zoneRatio < ratio)
    {
        //Width > expected
        float height = zoneRect.width / ratio;
        height /= viewWindowSize.y;
        switch (vAlign)
        {
        case ZoneVAlign::VCenter:
            ret.setViewport(sf::FloatRect(rect.left, rect.top + (rect.height - height) / 2.f, rect.width, height));
            break;
        case ZoneVAlign::VBottom:
            ret.setViewport(sf::FloatRect(rect.left, rect.top + (rect.height - height), rect.width, height));
            break;
        case ZoneVAlign::VTop:
            ret.setViewport(sf::FloatRect(rect.left, rect.top, rect.width, height));
            break;
        }
    }
    else
    {
        //Height > expected
        float width = zoneRect.height * ratio;
        width /= viewWindowSize.x;
        switch (hAlign)
        {
        case ZoneHAlign::HCenter:
            ret.setViewport(sf::FloatRect(rect.left + (rect.width - width) / 2.f, rect.top, width, rect.height));
            break;
        case ZoneHAlign::HRight:
            ret.setViewport(sf::FloatRect(rect.left + (rect.width - width), rect.top, width, rect.height));
            break;
        case ZoneHAlign::HLeft:
            ret.setViewport(sf::FloatRect(rect.left, rect.top, width, rect.height));
            break;
        }
    }
    calculatedView = ret;
}




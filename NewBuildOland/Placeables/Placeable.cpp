#include "Placeable.h"
#include "../Events/EventManager.h"

Placeable::Placeable(sf::IntRect textureRect, std::string name, sf::Color mapColor) :
    Item(name),
    textureRect(textureRect),
    mapColor(mapColor)
{
}


Placeable::~Placeable()
{
}

sf::Color Placeable::getColor()
{
	return mapColor;
}

sf::IntRect Placeable::getTextureRect()
{
	return textureRect;
}

sf::IntRect Placeable::getItemTextureRect() const
{
    return textureRect;
}

void Placeable::onPlaceableEnter(PlaceableEnterEvent e)
{
}
void Placeable::onPlaceableLeave(PlaceableLeaveEvent e)
{
}

bool Placeable::isPlaceable() {
	return true;
}

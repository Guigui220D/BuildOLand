#include "stdafx.h"
#include "Placeable.h"
#include "../Events/EventManager.h"

Placeable::Placeable(sf::IntRect textureRect, std::string name, sf::Color mapColor)
	:	textureRect(textureRect)
	,	name(name)
	,	mapColor(mapColor)
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

std::string Placeable::getName()
{
	return name;
}

void Placeable::OnPlaceableEnter(PlaceableEnterEvent e)
{
}
void Placeable::OnPlaceableLeave(PlaceableLeaveEvent e)
{
}
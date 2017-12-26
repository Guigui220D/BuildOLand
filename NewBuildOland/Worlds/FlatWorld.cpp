#include "stdafx.h"
#include "FlatWorld.h"


FlatWorld::FlatWorld()
{
}


FlatWorld::~FlatWorld()
{
}

unsigned short FlatWorld::getGround(sf::Vector2u pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= size.x || pos.y >= size.y)
		return 0;
	return (pos.x % 2 == 0);
}

unsigned short FlatWorld::getBlock(sf::Vector2u pos)
{
	return 0;
}

void FlatWorld::setGround(sf::Vector2u pos, unsigned short value)
{
}

void FlatWorld::setBlock(sf::Vector2u pos, unsigned short value)
{
}



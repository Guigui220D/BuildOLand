#include "stdafx.h"
#include "World.h"


World::World()
{
	
}

World::~World()
{
}

unsigned short World::getGround(sf::Vector2u pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= size.x || pos.y >= size.y)
		return 0;
	return 1;
}

unsigned short World::getBlock(sf::Vector2u pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= size.x || pos.y >= size.y)
		return 0;
	return 0;
}

void World::setGround(sf::Vector2u pos, unsigned short value)
{
}

void World::setBlock(sf::Vector2u pos, unsigned short value)
{
}

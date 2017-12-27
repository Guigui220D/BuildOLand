#include "stdafx.h"
#include "FlatWorld.h"
#include <iostream>


FlatWorld::FlatWorld(Game& game)
	: World(game)
{
	loadWorld();
	worldSize = sf::Vector2u(24, 24);
}


FlatWorld::~FlatWorld()
{
}

void FlatWorld::generateWorld() {

}

unsigned short FlatWorld::getGroundId(sf::Vector2u pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= worldSize.x || pos.y >= worldSize.y)
		return 0;
	return (pos.x % 2 == 0);
}

unsigned short FlatWorld::getBlockId(sf::Vector2u pos)
{
	return 0;
}

void FlatWorld::setGroundId(sf::Vector2u pos, unsigned short value)
{
}

void FlatWorld::setBlockId(sf::Vector2u pos, unsigned short value)
{
}

#include "stdafx.h"
#include "TestTileSet.h"
#include "../Utils/TileSet.h"

sf::IntRect TestTileSet::getGroundRect(unsigned int id)
{
	if (id == 0)
	{
		return sf::IntRect(0, 0, 8, 8);
	}
	else
	{
		return sf::IntRect(8, 8, 8, 8);
	}
}

sf::IntRect TestTileSet::getBlockRect(unsigned int id)
{
	return sf::IntRect(0, 0, 8, 8);
}

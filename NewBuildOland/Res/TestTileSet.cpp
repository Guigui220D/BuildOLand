#include "stdafx.h"
#include "TestTileSet.h"
#include "../Utils/TileSet.h"
#include <iostream>

TestTileSet::TestTileSet()
{
	texture = sf::Texture();
	//If this crashes, use the debug libs on the linker, add the -d
	texture.loadFromFile("testTile.png");
}

TestTileSet::~TestTileSet()
{
}

sf::IntRect TestTileSet::getGroundRect(unsigned int id)
{
	if (id == 0)
	{
		return sf::IntRect(0, 0, 8, 8);
	}
	else
	{
		return sf::IntRect(0, 8, 8, 8);
	}
}

sf::IntRect TestTileSet::getBlockRect(unsigned int id)
{
	return sf::IntRect(0, 0, 8, 8);
}

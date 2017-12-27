#include "stdafx.h"
#include "TileSet.h"

//This is the tileset class that allows to get textures from a block id
//All the tilsets should be in Res/

TileSet::TileSet()
{
	texture = sf::Texture();
	texture.loadFromFile("testTile.png");
}


TileSet::~TileSet()
{
}

sf::IntRect TileSet::getGroundRect(unsigned int id)
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

sf::IntRect TileSet::getBlockRect(unsigned int id)
{
	return sf::IntRect(0, 0, 8, 8);
}

sf::Texture* TileSet::getTexture()
{
	return &texture;
}


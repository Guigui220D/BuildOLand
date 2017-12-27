#include "stdafx.h"
#include "TileSet.h"

//This is the tileset class that allows to get textures from a block id
//All the tilsets should be in Res/

TileSet::TileSet(sf::Texture text)
{
	texture = text;
}


TileSet::~TileSet()
{
}

sf::IntRect TileSet::getGroundRect(unsigned int id)
{
	return sf::IntRect();
}

sf::IntRect TileSet::getBlockRect(unsigned int id)
{
	return sf::IntRect();
}


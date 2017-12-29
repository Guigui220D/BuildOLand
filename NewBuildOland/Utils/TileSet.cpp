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
	if (id < groundRectsSize)
		return groundRects[id];
	return errorRect;
}

sf::IntRect TileSet::getBlockRect(unsigned int id)
{
	if (id < blockRectsSize)
		return blockRects[id];
	return errorRect;
}

sf::Texture* TileSet::getTexture()
{
	return &texture;
}


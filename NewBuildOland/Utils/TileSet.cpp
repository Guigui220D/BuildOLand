#include "stdafx.h"
#include "TileSet.h"
#include <iostream>
//This is the tileset class that allows to get textures from a block id
//All the tilsets should be in Res/

TileSet::TileSet()
{
	texture = sf::Texture();
	generateBlocks();
	generateGrounds();
	texture.loadFromFile("testTile.png");
}

void TileSet::generateBlocks()
{
	blocks.push_back(new Block(rectById(1), "AIR"));
	blocks.push_back(new Block(rectById(5), "CHAIN", sf::Color(255, 255, 0)));
}

void TileSet::generateGrounds()
{
	grounds.push_back(new Ground(rectById(2), "GRASS", sf::Color(0, 64, 0)));
	grounds.push_back(new Ground(rectById(4), "WATER", sf::Color(32, 32, 128)));
	grounds.push_back(new Ground(rectById(3), "SAND", sf::Color(128, 64, 32)));
}

sf::IntRect TileSet::rectById(unsigned int tilesetId)
{
	//Creates an IntRect where the texture is according to the nth texture of the tileset
	return sf::IntRect(tilesetId % TILES_IN_ROW * TILE_SIZE, floorf(tilesetId / TILES_IN_ROW) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

}

TileSet::~TileSet()
{
}

sf::IntRect TileSet::getGroundRect(unsigned int id)
{

	if (id < grounds.size()) {
		return grounds[id]->getTextureRect();
	}	

	return errorRect;
}

sf::IntRect TileSet::getBlockRect(unsigned int id)
{

	if (id < blocks.size()) {
		return blocks[id]->getTextureRect();
	}

	return errorRect;
}


sf::Color TileSet::getMapPixel(unsigned int groundId, unsigned int blockId)
{
	if (blockId > 0 && blockId < blocks.size())
		return blocks[blockId]->getColor();
	if (groundId < grounds.size())
		return grounds[groundId]->getColor();
	return errorColor;
}

sf::Texture* TileSet::getTexture()
{
	return &texture;
}


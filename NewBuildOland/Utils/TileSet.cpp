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
	texture.loadFromFile("Res/tileset.png");
}

void TileSet::generateBlocks()
{
	blocks.push_back(new Block(rectById(1), "AIR"));
	blocks.push_back(new Block(rectById(7), "BARRIER", sf::Color(90, 70, 50)));
	blocks.push_back(new Block(rectById(6), "BRICK", sf::Color(90, 90, 90)));
	blocks.push_back(new Block(rectById(8), "PRESSURE_PLATE",	sf::Color(135, 30, 30)));
}

void TileSet::generateGrounds()
{
	grounds.push_back(new Ground(rectById(2), "GRASS", sf::Color(135, 170, 55)));
	grounds.push_back(new Ground(rectById(3), "SAND", sf::Color(215, 215, 60)));
	grounds.push_back(new Ground(rectById(4), "WATER", sf::Color(60, 90, 210)));
	grounds.push_back(new Ground(rectById(5), "CONCRETE", sf::Color(155, 155, 155)));
}

sf::IntRect TileSet::rectById(unsigned int tilesetId)
{
	//Creates an IntRect where the texture is according to the nth texture of the tileset
	return sf::IntRect(tilesetId % TILES_IN_ROW * TILE_SIZE, (int)floorf(tilesetId / TILES_IN_ROW) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

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


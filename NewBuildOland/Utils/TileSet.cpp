#include "TileSet.h"
#include "../Placeables/BlockTeleporter.h"
#include "../Placeables/BlockSaver.h"
#include "../Placeables/TNTBlock.h"
#include "../Placeables/GroundGrass.h"
#include "../Placeables/WornConcrete.h"
#include "../Placeables/OpenDoorBlock.h"
#include "../Placeables/ClosedDoorBlock.h"
#include "../Placeables/BlinkerBlock.h"
#include <iostream>
#include <math.h>
//This is the tileset class that allows to get textures from a block id
//All the tilsets should be in Res/

TileSet::TileSet()
{
	texture = sf::Texture();
	generateBlocks();
	generateGrounds();

	texture.loadFromFile("Res/newTileset.png");
}

void TileSet::generateBlocks()
{
	blocks.push_back(new Block(rectById(1), "AIR",				sf::Color(90, 70, 50),	false, false));                 //0
	blocks.push_back(new Block(rectById(7), "LOG",				sf::Color(135, 90, 30),	true, true, rectById(12)));     //1
	blocks.push_back(new Block(rectById(6), "BRICK",			sf::Color(90, 90, 90),	true));                         //2
	blocks.push_back(new Block(rectById(5), "CONCRETE",			sf::Color(90, 90, 90),	true));                         //3
	blocks.push_back(new Block(rectById(15), "METAL",			sf::Color(200, 200, 200),true));                        //4
	blocks.push_back(new Block(rectById(16), "GOLD",			sf::Color(255, 255, 200),true));                        //5
	blocks.push_back(new TNTBlock(rectById(17), rectById(18)));                                                         //6
    blocks.push_back(new ClosedDoorBlock(rectById(22), rectById(20)));                                                  //7
    blocks.push_back(new OpenDoorBlock(rectById(23), rectById(21)));                                                    //8
	blocks.push_back(new Block(rectById(8), "PRESSURE_PLATE",   sf::Color(135, 30, 30), false, false));                 //9
	blocks.push_back(new BlockSaver(rectById(10)));                                                                     //10
	blocks.push_back(new BlockTeleporter(rectById(11)));                                                                //11
	blocks.push_back(new BlinkerBlock(rectById(17), rectById(12)));                                                     //12

}

void TileSet::generateGrounds()
{
	grounds.push_back(new GroundGrass(rectById(2)));
	grounds.push_back(new Ground(rectById(3), "SAND", sf::Color(215, 215, 60)));
	grounds.push_back(new Ground(rectById(4), "WATER", sf::Color(60, 90, 210)));
	grounds.push_back(new Ground(rectById(5), "CONCRETE", sf::Color(155, 155, 155)));
	grounds.push_back(new WornConcrete(rectById(19), "WORN_CONCRETE", sf::Color(135, 135, 135)));
}

sf::IntRect TileSet::rectById(unsigned int tilesetId)
{
	//Creates an IntRect where the texture is according to the nth texture of the tileset
	return sf::IntRect(tilesetId % TILES_IN_ROW * (TILE_SIZE + 2) + 1, (int)floorf(tilesetId / TILES_IN_ROW) * (TILE_SIZE + 2) + 1, TILE_SIZE, TILE_SIZE);

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

sf::IntRect TileSet::getBlockSideRect(unsigned int id)
{
	if (id < blocks.size()) {
		sf::IntRect side = blocks[id]->getSideRect();
		if (side == sf::IntRect())
			return blocks[id]->getTextureRect();
		return side;
	}
	return errorRect;
}

Ground* TileSet::getGroundById(unsigned int id) {
	return grounds[id];
}

Block* TileSet::getBlockById(unsigned int id) {
	return blocks[id];
}

Block *TileSet::getBlockByName(std::string name) {
	return getBlockById(getBlockIdByName(name));
}

Ground *TileSet::getGroundByName(std::string name) {
	return getGroundById(getGroundIdByName(name));
}


sf::Color TileSet::getMapPixel(unsigned int groundId, unsigned int blockId)
{
	if (blockId > 0 && blockId < blocks.size())
		return blocks[blockId]->getColor();
	if (groundId < grounds.size())
		return grounds[groundId]->getColor();
	return errorColor;
}

sf::Color TileSet::getSideTint(unsigned int id)
{
	if (id < blocks.size()) {
		return blocks[id]->getSideTint();
	}
	return sf::Color::White;
}

sf::Texture* TileSet::getTexture()
{
	return &texture;
}

unsigned int TileSet::getTotalBlockNb()
{
	return blocks.size();
}
unsigned int TileSet::getTotalGroundNb()
{
	return blocks.size();
}

unsigned short TileSet::getBlockIdByName(std::string name) {
	for(unsigned short i = 0; i < blocks.size(); i++) {
		if(blocks[i]->getName() == name) {
			return i;
		}
	}

	return 0;
}

unsigned short TileSet::getGroundIdByName(std::string name) {
	for(unsigned short i = 0; i < grounds.size(); i++) {
		if(grounds[i]->getName() == name) {
			return i;
		}
	}

	return 0;
}

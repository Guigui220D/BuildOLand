#include "TileSet.h"
#include "../Placeables/EngineeringBlocks/BlockSaver.h"
#include "../Placeables/EngineeringBlocks/TNTBlock.h"
#include "../Placeables/Grounds/GroundGrass.h"
#include "../Placeables/Grounds/WornConcrete.h"
#include "../Placeables/BuildingBlocks/OpenDoorBlock.h"
#include "../Placeables/BuildingBlocks/ClosedDoorBlock.h"
#include "../Placeables/Prototypes/BlinkerBlock.h"
#include <iostream>
//This is the tileset class that allows to get textures from a block id
//The tileset should be in Res/

TileSet::TileSet()
{
    tileset = GameGlobal::assets.getTexture("TILESET");
	generateBlocks();
	generateGrounds();
}

TileSet::~TileSet()
{
    for (Block* b : blocks)
        delete b;
    for (Ground* g : grounds)
        delete g;
}

void TileSet::addTile(Placeable* tile)
{
    std::string name = tile->getName();
    if (tile->isGround())
    {
        if (groundNames.find(name) == blockNames.end())
        {
            Ground* ground = (Ground*)tile;
            //Add the ground
            grounds.push_back(ground);
            unsigned short id = grounds.size() - 1;
            ground->setTileId(id);
            //Add the name in the map
            groundNames.emplace(std::pair<std::string, unsigned short>(name, id));
        }
        else
            std::cerr << "A ground with the name \"" << name << "\" already exists, could not add it.\n";
    }
    else
    {
        if (blockNames.find(name) == blockNames.end())
        {
            Block* block = (Block*)tile;
            //Add the block
            blocks.push_back(block);
            unsigned short id = blocks.size() - 1;
            block->setTileId(id);
            //Add the name in the map
            blockNames.emplace(std::pair<std::string, unsigned short>(name, id));
        }
        else
            std::cerr << "A block with the name \"" << name <<"\" already exists, could not add it.\n";
    }
    return;
}

void TileSet::generateBlocks()
{
	addTile(new Block(rectById(1), "AIR",				sf::Color(90, 70, 50),	false, false));                 //0
	addTile(new Block(rectById(7), "LOG",				sf::Color(135, 90, 30),	true, true, rectById(12)));     //1
	addTile(new Block(rectById(6), "BRICK",			    sf::Color(90, 90, 90),	true));                         //2
	addTile(new Block(rectById(5), "CONCRETE",			sf::Color(90, 90, 90),	true));                         //3
	addTile(new Block(rectById(15), "METAL",			sf::Color(200, 200, 200),true));                        //4
	addTile(new Block(rectById(16), "GOLD",			    sf::Color(255, 255, 200),true));                        //5
	addTile(new TNTBlock(rectById(17), rectById(18)));                                                         //6
    addTile(new ClosedDoorBlock(rectById(22), rectById(20)));                                                  //7
    addTile(new OpenDoorBlock(rectById(23), rectById(21)));                                                    //8
	addTile(new Block(rectById(8), "PRESSURE_PLATE",   sf::Color(135, 30, 30), false, false));                 //9
	addTile(new BlockSaver(rectById(10)));                                                                     //10                                                          //11
	addTile(new BlinkerBlock(rectById(17), rectById(12)));                                                     //12

}

void TileSet::generateGrounds()
{
	addTile(new GroundGrass(rectById(2)));
	addTile(new Ground(rectById(3), "SAND", sf::Color(215, 215, 60)));
	addTile(new Ground(rectById(4), "WATER", sf::Color(60, 90, 210)));
	addTile(new Ground(rectById(5), "CONCRETE", sf::Color(155, 155, 155)));
	addTile(new WornConcrete(rectById(19), "WORN_CONCRETE", sf::Color(135, 135, 135)));
}

sf::IntRect TileSet::getBlockSideRect(unsigned int id) const
{
	if (id < blocks.size())
    {
		sf::IntRect side = blocks.at(id)->getSideRect();
		if (side == sf::IntRect())
			return blocks.at(id)->getTextureRect();
		return side;
	}
	return errorRect;
}

sf::Color TileSet::getMapPixel(unsigned int groundId, unsigned int blockId) const
{
	if (blockId > 0 && blockId < blocks.size())
		return blocks[blockId]->getColor();
	if (groundId < grounds.size())
		return grounds[groundId]->getColor();
	return errorColor;
}

unsigned short TileSet::getBlockIdByName(const std::string name) const
{
    auto i = blockNames.find(name);
    return (i != blockNames.end()) ? (i->second) : 0;
}

unsigned short TileSet::getGroundIdByName(const std::string name) const
{
    auto i = groundNames.find(name);
    return ((i != groundNames.end()) ? (i->second) : 0);
}

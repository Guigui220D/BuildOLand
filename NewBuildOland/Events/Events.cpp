#include "stdafx.h"
#include <iostream>
#include "Events.h"
#include "../States/StateGame.h"


TileSet* Events::tileset;

Events::Events()
{
}


Events::~Events()
{
}

void Events::OnBlockBreak(BlockBreakEvent e)
{
	std::cout << "Event : Block " << tileset->getBlockById(e.getOldBlock())->getName() << " broken at " << e.getPosition().x << ", " << e.getPosition().y << std::endl;

	//Send event to the block
	tileset->getBlockById(e.getOldBlock())->OnBlockBreak(e);	
}

void Events::OnBlockBuild(BlockBuildEvent e)
{
	std::cout << "Event : Block " << e.getBlock() << " built at " << e.getPosition().x << ", " << e.getPosition().y << std::endl;
	
	//Send event to the block
	tileset->getBlockById(e.getBlock())->OnBlockBuild(e);
}

void Events::OnPlaceableEnter(PlaceableEnterEvent e)
{
	//Send event to the block
	tileset->getBlockById(e.getBlockId())->OnPlaceableEnter(e);

	//TODO: Send event to the ground
}

void Events::OnPlaceableLeave(PlaceableLeaveEvent e)
{

}

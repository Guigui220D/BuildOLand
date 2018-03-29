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

void Events::OnWalkOnBlock(WalkOnEvent e)
{
	if (e.getBlockId() == 4)
	{
		//e.getState()->getWorld()->saveWorld();
		std::cout << "Saved the world!" << std::endl;
		std::cout << "TODO : Le monde n'a pas ete save, ceci necessiterait que la classe entity ait acces a sa state" << std::endl;
	}
}

void Events::OnLeaveBlock(BlockLeaveEvent e)
{

}

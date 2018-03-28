#include "stdafx.h"
#include <iostream>
#include "Events.h"

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
	if (e.getOldBlock() == 4 && e.getPosition() == sf::Vector2u())
	{
		e.getState()->getWorld()->setBlockId(e.getPosition(), 4);
		e.getState()->getWorld()->saveWorld();
		std::cout << "Saved the world!" << std::endl;
	}
}

void Events::OnBlockBuild(BlockBuildEvent e)
{
	std::cout << "Event : Block " << e.getBlock() << " built at " << e.getPosition().x << ", " << e.getPosition().y << std::endl;
}

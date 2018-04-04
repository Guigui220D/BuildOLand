#include <iostream>
#include "EventManager.h"
#include "../States/StateGame.h"


TileSet* EventManager::tileset;

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::OnBlockBreak(BlockBreakEvent e)
{
	std::cout << "Event : Block " << tileset->getBlockById(e.getOldBlock())->getName() << " broken at " << e.getPosition().x << ", " << e.getPosition().y << std::endl;

	//Send event to the block
	tileset->getBlockById(e.getOldBlock())->OnBlockBreak(e);
}

void EventManager::OnBlockBuild(BlockBuildEvent e)
{
	std::cout << "Event : Block " << e.getBlock() << " built at " << e.getPosition().x << ", " << e.getPosition().y << std::endl;

	//Send event to the block
	tileset->getBlockById(e.getBlock())->OnBlockBuild(e);
}

void EventManager::OnPlaceableEnter(PlaceableEnterEvent e)
{
	//Send event to the block
	tileset->getBlockById(e.getBlockId())->OnPlaceableEnter(e);

	//TODO: Send event to the ground
}

void EventManager::OnPlaceableLeave(PlaceableLeaveEvent e)
{

}

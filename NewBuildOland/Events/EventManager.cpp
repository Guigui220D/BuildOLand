#include <iostream>
#include "EventManager.h"
#include "../States/StateGame.h"
#include "GroundPlaceEvent.h"


TileSet* EventManager::tileset;

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::OnBlockBreak(BlockBreakEvent e)
{
	//std::cout << "Event : Block " << tileset->getBlockById(e.getOldBlock())->getName() << " broken at " << e.getPosition().x << ", " << e.getPosition().y << "\n";

	//Send event to the block
	tileset->getBlockById(e.getOldBlock())->OnBlockBreak(e);
}

void EventManager::OnBlockBuild(BlockBuildEvent e)
{
	//std::cout << "Event : Block " << e.getBlock() << " built at " << e.getPosition().x << ", " << e.getPosition().y << "\n";

	//Send event to the block
	tileset->getBlockById(e.getBlock())->OnBlockBuild(e);
}

void EventManager::OnGroundPlace(GroundPlaceEvent e)
{
	//std::cout << "Event : Ground " << e.getNewGround() << " placed at " << e.getPosition().x << ", " << e.getPosition().y << "\n";

	//Send event to the block
//    tileset->getGroundById(e.getNewGround())->OnGroundPlaced(e);
//    tileset->getGroundById(e.getNewGround())->OnGroundRePlaced(e);
}

void EventManager::OnPlaceableEnter(PlaceableEnterEvent e)
{
	//Send event to the block
	tileset->getBlockById(e.getBlockId())->OnPlaceableEnter(e);

	//Send event to the ground
	tileset->getGroundById(e.getGroundId())->OnPlaceableEnter(e);

}

void EventManager::OnPlaceableLeave(PlaceableLeaveEvent e)
{

}

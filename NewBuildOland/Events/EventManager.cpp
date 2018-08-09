#include <iostream>
#include "EventManager.h"
#include "../States/StateGame.h"

TileSet* EventManager::tileset;
StateGame* EventManager::state;

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::OnBlockBreak(BlockBreakEvent e)
{
	if (!state->isOnlineAndAvailible())
    {
        //Send event to the block
        tileset->getBlockById(e.getOldBlock())->onBlockBreak(e);
    }
    //else    //To server
        //state->getNetworkManager()->sendBlockBreak(e.getPosition());
}

void EventManager::OnBlockBuild(BlockBuildEvent e)
{
    if (!state->isOnlineAndAvailible())
    {
        //Send event to the block
        tileset->getBlockById(e.getBlock())->onBlockBuild(e);
    }
    //else    //To server
        //state->getNetworkManager()->sendBlockBuild(e.getPosition(), e.getBlock());
}

void EventManager::OnGroundPlace(GroundPlaceEvent e)
{
	//Send event to the block
//    tileset->getGroundById(e.getNewGround())->OnGroundPlaced(e);
//    tileset->getGroundById(e.getNewGround())->OnGroundRePlaced(e);

    //if (state->isOnlineAndAvailible())  //Send event to server
        //state->getNetworkManager()->sendGroundChange(e.getPosition(), e.getNewGround());
}

void EventManager::OnPlaceableEnter(PlaceableEnterEvent e)
{
    if (!state->isOnlineAndAvailible())
    {
        //Send events to tiles
        tileset->getBlockById(e.getBlockId())->onPlaceableEnter(e);
        tileset->getGroundById(e.getGroundId())->onPlaceableEnter(e);
    }
    //Automatically handled by server
}

void EventManager::OnPlaceableLeave(PlaceableLeaveEvent e)
{

}

void EventManager::OnBlockInteract(BlockInteractEvent e)
{
    if (!state->isOnlineAndAvailible())
    {
        //Send event to block
        tileset->getBlockById(e.getBlock())->onBlockInteract(e);
    }
    //else    //To server
        //state->getNetworkManager()->sendInteractEvent(e.getPosition());
}

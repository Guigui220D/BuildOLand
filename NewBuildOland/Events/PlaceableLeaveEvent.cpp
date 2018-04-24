#include "PlaceableLeaveEvent.h"

PlaceableLeaveEvent::PlaceableLeaveEvent(sf::Vector2u pos, Player* player, unsigned short blockId, unsigned short groundId, StateGame * state) : GameEvent(state)
{
	tilePos = pos;
	entit = player;
	PlaceableLeaveEvent::blockId = blockId;
	PlaceableLeaveEvent::groundId = groundId;
}

PlaceableLeaveEvent::~PlaceableLeaveEvent()
{
}

sf::Vector2u PlaceableLeaveEvent::getTilePos()
{
	return tilePos;
}

Player* PlaceableLeaveEvent::getPlayer()
{
	return entit;
}

unsigned short PlaceableLeaveEvent::getBlockId()
{
	return blockId;
}

unsigned short PlaceableLeaveEvent::getGroundId()
{
	return groundId;
}
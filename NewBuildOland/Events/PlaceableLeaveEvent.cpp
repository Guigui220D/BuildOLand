#include "stdafx.h"
#include "PlaceableLeaveEvent.h"

PlaceableLeaveEvent::PlaceableLeaveEvent(sf::Vector2u pos, Player* player, unsigned short id, StateGame * state) : GameEvent(state)
{
	tilePos = pos;
	entit = player;
	blockId = id;
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
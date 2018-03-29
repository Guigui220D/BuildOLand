#include "stdafx.h"
#include "BlockLeaveEvent.h"

BlockLeaveEvent::BlockLeaveEvent(sf::Vector2u pos, Player* player, unsigned short id, StateGame * state) : GameEvent(state)
{
	tilePos = pos;
	entit = player;
	blockId = id;
}

BlockLeaveEvent::~BlockLeaveEvent()
{
}

sf::Vector2u BlockLeaveEvent::getTilePos()
{
	return tilePos;
}

Player* BlockLeaveEvent::getPlayer()
{
	return entit;
}

unsigned short BlockLeaveEvent::getBlockId()
{
	return blockId;
}

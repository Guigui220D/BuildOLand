#include "stdafx.h"
#include "WalkOnEvent.h"

WalkOnEvent::WalkOnEvent(sf::Vector2u pos, Player* player, unsigned short id, StateGame * state) : GameEvent(state)
{
	tilePos = pos;
	entit = player;
	blockId = id;
}

WalkOnEvent::~WalkOnEvent()
{
}

sf::Vector2u WalkOnEvent::getTilePos()
{
	return tilePos;
}

Player* WalkOnEvent::getPlayer()
{
	return entit;
}

unsigned short WalkOnEvent::getBlockId()
{
	return blockId;
}

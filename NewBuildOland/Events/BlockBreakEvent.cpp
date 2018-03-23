#include "stdafx.h"
#include "BlockBreakEvent.h"


BlockBreakEvent::BlockBreakEvent(sf::Vector2i pos, unsigned int oldblock, Entities entity)
{
	oldBlock = oldblock;
	position = pos;
	entit = entity;
}

BlockBreakEvent::~BlockBreakEvent()
{
}

sf::Vector2i BlockBreakEvent::getPosition()
{
	return position;
}

unsigned int BlockBreakEvent::getOldBlock()
{
	return oldBlock;
}

Entities BlockBreakEvent::getEntity()
{
	return entit;
}

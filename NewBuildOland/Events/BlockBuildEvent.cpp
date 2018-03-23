#include "stdafx.h"
#include "BlockBuildEvent.h"


BlockBuildEvent::BlockBuildEvent(sf::Vector2i pos, unsigned int newblock, Entities entity)
{
	newBlock = newblock;
	position = pos;
	entit = entity;
}


BlockBuildEvent::~BlockBuildEvent()
{
}

sf::Vector2i BlockBuildEvent::getPosition()
{
	return position;
}

unsigned int BlockBuildEvent::getBlock()
{
	return newBlock;
}

Entities BlockBuildEvent::getEntity()
{
	return entit;
}

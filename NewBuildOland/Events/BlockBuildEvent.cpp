#include "stdafx.h"
#include "BlockBuildEvent.h"
#include "../States/StateGame.h"
#include "../Entities/Entities.h"

BlockBuildEvent::BlockBuildEvent(sf::Vector2u pos, unsigned int newblock, Entities entity, StateGame* state) : GameEvent(state)
{
	newBlock = newblock;
	position = pos;
	entit = entity;
}


BlockBuildEvent::~BlockBuildEvent()
{
}

sf::Vector2u BlockBuildEvent::getPosition()
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

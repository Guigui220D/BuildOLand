#include "BlockBuildEvent.h"

BlockBuildEvent::BlockBuildEvent(sf::Vector2u pos, unsigned int newblock, Entities* entity, StateGame* state) : GameEvent(state)
{
	newBlock = newblock;
	position = pos;
	entit = entity;
}


BlockBuildEvent::~BlockBuildEvent()
{
}

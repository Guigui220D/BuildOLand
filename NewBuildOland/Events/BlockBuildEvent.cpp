#include "BlockBuildEvent.h"

BlockBuildEvent::BlockBuildEvent(sf::Vector2i pos, unsigned int newblock, Entities* entity, StateGame* state) : GameEvent(state)
{
	newBlock = newblock;
	position = pos;
	entit = entity;
}


BlockBuildEvent::~BlockBuildEvent()
{
}

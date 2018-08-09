#include "BlockBreakEvent.h"
#include "../States/StateGame.h"

BlockBreakEvent::BlockBreakEvent(sf::Vector2i pos, unsigned int oldblock, Entities* entity, StateGame* state) : GameEvent(state)
{
	oldBlock = oldblock;
	position = pos;
	entit = entity;
}

BlockBreakEvent::~BlockBreakEvent()
{
}


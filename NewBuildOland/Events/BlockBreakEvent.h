#pragma once
#include "SFML\System.hpp"
#include "../Entities/Entities.h"
#include "GameEvent.h"

class BlockBreakEvent : public GameEvent
{
public:
	BlockBreakEvent(sf::Vector2i pos, unsigned int oldblock, Entities entity);
	~BlockBreakEvent();
	sf::Vector2i getPosition();
	unsigned int getOldBlock();
	Entities getEntity();
protected:
	sf::Vector2i position;
	unsigned int oldBlock;
	Entities entit;
};


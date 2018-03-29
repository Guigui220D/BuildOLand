#pragma once
#include "SFML\System.hpp"
#include "../Entities/Entities.h"
#include "GameEvent.h"

class BlockBreakEvent : public GameEvent
{
public:
	BlockBreakEvent(sf::Vector2u pos, unsigned int oldblock, Entities* entity, StateGame* state);
	~BlockBreakEvent();
	sf::Vector2u getPosition();
	unsigned int getOldBlock();
	Entities* getEntity();
protected:
	sf::Vector2u position;
	unsigned int oldBlock;
	Entities* entit;
};


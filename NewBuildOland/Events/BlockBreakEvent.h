#pragma once
#include "SFML\System.hpp"
#include "../Entities/Entities.h"
#include "GameEvent.h"

class BlockBreakEvent : public GameEvent
{
public:
	BlockBreakEvent(sf::Vector2i pos, unsigned int oldblock, Entities* entity, StateGame* state);
	~BlockBreakEvent();
	inline sf::Vector2i getPosition() { return position; };
	inline unsigned int getOldBlock() { return oldBlock; };
	inline Entities* getEntity() { return entit; };
protected:
	sf::Vector2i position;
	unsigned int oldBlock;
	Entities* entit;
};


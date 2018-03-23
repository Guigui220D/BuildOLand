#pragma once
#include "SFML\System.hpp"
#include "../Entities/Entities.h"
#include "GameEvent.h"

class BlockBuildEvent : public GameEvent
{
public:
	BlockBuildEvent(sf::Vector2i pos, unsigned int newblock, Entities entity);
	~BlockBuildEvent();
	sf::Vector2i getPosition();
	unsigned int getBlock();
	Entities getEntity();
protected:
	sf::Vector2i position;
	unsigned int newBlock;
	Entities entit;
};


#pragma once
#include "SFML\System.hpp"
//#include "../Entities/Entities.h"
#include "GameEvent.h"
//#include "../States/StateGame.h"

class BlockBuildEvent : public GameEvent
{
public:
	BlockBuildEvent(sf::Vector2u pos, unsigned int newblock, Entities entity, StateGame* state);
	~BlockBuildEvent();
	sf::Vector2u getPosition();
	unsigned int getBlock();
	Entities getEntity();
protected:
	sf::Vector2u position;
	unsigned int newBlock;
	Entities entit;
};


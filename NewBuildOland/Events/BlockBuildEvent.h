#pragma once
#include "SFML\System.hpp"
//#include "../Entities/Entities.h"
#include "GameEvent.h"
//#include "../States/StateGame.h"

class BlockBuildEvent : public GameEvent
{
public:
	BlockBuildEvent(sf::Vector2i pos, unsigned int newblock, Entities* entity, StateGame* state);
	~BlockBuildEvent();
	inline sf::Vector2i getPosition() { return position; };
	inline unsigned int getBlock() { return newBlock; };
	inline Entities* getEntity() { return entit; };
protected:
	sf::Vector2i position;
	unsigned int newBlock;
	Entities* entit;
};


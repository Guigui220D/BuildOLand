#pragma once
#include "SFML\System.hpp"
#include "../Entities/Player.h"
#include "GameEvent.h"

class WalkOnEvent : public GameEvent
{
public:
	WalkOnEvent(sf::Vector2u pos, Player* player, unsigned short id, StateGame* state);
	~WalkOnEvent();
	sf::Vector2u getTilePos();
	Player* getPlayer();
	unsigned short getBlockId();
protected:
	Player* entit;
	sf::Vector2u tilePos;
	unsigned short blockId;
};


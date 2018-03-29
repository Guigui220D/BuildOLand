#pragma once
#include "SFML\System.hpp"
#include "../Entities/Player.h"
#include "GameEvent.h"

class BlockLeaveEvent : public GameEvent
{
public:
	BlockLeaveEvent(sf::Vector2u pos, Player* player, unsigned short id, StateGame* state);
	~BlockLeaveEvent();
	sf::Vector2u getTilePos();
	Player* getPlayer();
	unsigned short getBlockId();
protected:
	Player * entit;
	sf::Vector2u tilePos;
	unsigned short blockId;
};


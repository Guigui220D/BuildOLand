#pragma once
#include "SFML\System.hpp"
#include "../Entities/Player.h"
#include "GameEvent.h"

class PlaceableLeaveEvent : public GameEvent
{
public:
	PlaceableLeaveEvent(sf::Vector2u pos, Player* player, unsigned short blockId, unsigned short groundId, StateGame* state);
	~PlaceableLeaveEvent();
	sf::Vector2u getTilePos();
	Player* getPlayer();
	unsigned short getBlockId();
	unsigned short getGroundId();
protected:
	Player * entit;
	sf::Vector2u tilePos;
	unsigned short blockId;
	unsigned short groundId;
};


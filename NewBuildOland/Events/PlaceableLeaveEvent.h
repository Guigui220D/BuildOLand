#pragma once
#include "SFML\System.hpp"
#include "../Entities/Player.h"
#include "GameEvent.h"

class PlaceableLeaveEvent : public GameEvent
{
public:
	PlaceableLeaveEvent(sf::Vector2i pos, Player* player, unsigned short blockId, unsigned short groundId, StateGame* state);
	~PlaceableLeaveEvent();
	inline sf::Vector2i getTilePos() { return tilePos; };
	inline Player* getPlayer() { return entit; };
	inline unsigned short getBlockId() { return blockId; };
	inline unsigned short getGroundId() { return groundId; };
protected:
	Player* entit;
	sf::Vector2i tilePos;
	unsigned short blockId;
	unsigned short groundId;
};


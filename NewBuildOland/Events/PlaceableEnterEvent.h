#pragma once
#include "SFML\System.hpp"
#include "../Entities/Player.h"
#include "GameEvent.h"

class PlaceableEnterEvent : public GameEvent
{
public:
	PlaceableEnterEvent(sf::Vector2u pos, Player* player, unsigned short blockId, unsigned short groundId, StateGame* state);
	~PlaceableEnterEvent();
	inline sf::Vector2u getTilePos() { return tilePos; };
	inline Player* getPlayer() { return entit; };
	inline unsigned short getBlockId() { return blockId; };
	inline unsigned short getGroundId() { return groundId; };
protected:
	Player* entit;
	sf::Vector2u tilePos;
	unsigned short blockId;
	unsigned short groundId;
};


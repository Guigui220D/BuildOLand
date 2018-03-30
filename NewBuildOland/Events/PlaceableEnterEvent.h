#pragma once
#include "SFML\System.hpp"
#include "../Entities/Player.h"
#include "GameEvent.h"

class PlaceableEnterEvent : public GameEvent
{
public:
	PlaceableEnterEvent(sf::Vector2u pos, Player* player, unsigned short id, StateGame* state);
	~PlaceableEnterEvent();
	sf::Vector2u getTilePos();
	Player* getPlayer();
	unsigned short getBlockId();
protected:
	Player* entit;
	sf::Vector2u tilePos;
	unsigned short blockId;
};


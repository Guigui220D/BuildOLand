#include "PlaceableEnterEvent.h"

PlaceableEnterEvent::PlaceableEnterEvent(sf::Vector2u pos, Player* player, unsigned short id, StateGame * state) : GameEvent(state)
{
	tilePos = pos;
	entit = player;
	blockId = id;
}

PlaceableEnterEvent::~PlaceableEnterEvent()
{
}

sf::Vector2u PlaceableEnterEvent::getTilePos()
{
	return tilePos;
}

Player* PlaceableEnterEvent::getPlayer()
{
	return entit;
}

unsigned short PlaceableEnterEvent::getBlockId()
{
	return blockId;
}

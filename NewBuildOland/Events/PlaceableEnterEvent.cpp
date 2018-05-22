#include "PlaceableEnterEvent.h"

PlaceableEnterEvent::PlaceableEnterEvent(sf::Vector2u pos, Player* player, unsigned short blockId, unsigned short groundId, StateGame * state) : GameEvent(state)
{
	tilePos = pos;
	entit = player;
	PlaceableEnterEvent::blockId = blockId;
	PlaceableEnterEvent::groundId = groundId;
}

PlaceableEnterEvent::~PlaceableEnterEvent()
{
}

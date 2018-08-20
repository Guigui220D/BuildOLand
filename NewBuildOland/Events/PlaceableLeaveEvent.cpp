#include "PlaceableLeaveEvent.h"

PlaceableLeaveEvent::PlaceableLeaveEvent(sf::Vector2i pos, Player* player, unsigned short blockId, unsigned short groundId, StateGame * state) : GameEvent(state)
{
	tilePos = pos;
	entit = player;
	PlaceableLeaveEvent::blockId = blockId;
	PlaceableLeaveEvent::groundId = groundId;
}

PlaceableLeaveEvent::~PlaceableLeaveEvent()
{
}

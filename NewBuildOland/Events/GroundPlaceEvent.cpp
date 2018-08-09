#include "GroundPlaceEvent.h"

GroundPlaceEvent::GroundPlaceEvent(sf::Vector2i pos, unsigned int oldGroundId, unsigned int newGroundId, Entities* entity, StateGame* state)
    : GameEvent(state)
    , pos(pos)
    , oldGroundId(oldGroundId)
    , newGroundId(newGroundId)
    , entity(entity)
{
}

GroundPlaceEvent::~GroundPlaceEvent() {

}

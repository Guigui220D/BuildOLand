#include "GroundPlaceEvent.h"

GroundPlaceEvent::GroundPlaceEvent(sf::Vector2u pos, unsigned int oldGroundId, unsigned int newGroundId, Entities* entity, StateGame* state)
    : GameEvent(state)
    , pos(pos)
    , oldGroundId(oldGroundId)
    , newGroundId(newGroundId)
    , entity(entity)
{
}

GroundPlaceEvent::~GroundPlaceEvent() {

}

sf::Vector2u GroundPlaceEvent::getPosition() {
    return pos;
}

unsigned int GroundPlaceEvent::getNewGround() {
    return newGroundId;
}

unsigned int GroundPlaceEvent::getOldGround() {
    return oldGroundId;
}

Entities *GroundPlaceEvent::getEntity() {
    return entity;
}

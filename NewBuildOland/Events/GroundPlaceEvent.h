
#pragma once


#include "../Entities/Entities.h"
#include "GameEvent.h"

class GroundPlaceEvent : public GameEvent {
public:
    GroundPlaceEvent(sf::Vector2i pos, unsigned int oldGroundId, unsigned int newGroundId, Entities* entity, StateGame* state);

    ~GroundPlaceEvent();
    inline sf::Vector2i getPosition() { return pos; };
    inline unsigned int getNewGround() { return newGroundId; };
    inline unsigned int getOldGround() { return oldGroundId; };
    inline Entities* getEntity() { return entity; };

protected:
    sf::Vector2i pos;
    unsigned int oldGroundId;
    unsigned int newGroundId;
    Entities* entity;
};




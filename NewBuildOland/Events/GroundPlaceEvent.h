
#pragma once


#include "../Entities/Entities.h"
#include "GameEvent.h"

class GroundPlaceEvent : public GameEvent {
public:
    GroundPlaceEvent(sf::Vector2u pos, unsigned int oldGroundId, unsigned int newGroundId, Entities* entity, StateGame* state);

    ~GroundPlaceEvent();
    inline sf::Vector2u getPosition() { return pos; };
    inline unsigned int getNewGround() { return newGroundId; };
    inline unsigned int getOldGround() { return oldGroundId; };
    inline Entities* getEntity() { return entity; };

protected:
    sf::Vector2u pos;
    unsigned int oldGroundId;
    unsigned int newGroundId;
    Entities* entity;
};




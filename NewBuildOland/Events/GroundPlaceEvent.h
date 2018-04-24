
#pragma once


#include "../Entities/Entities.h"
#include "GameEvent.h"

class GroundPlaceEvent : public GameEvent {
public:
    GroundPlaceEvent(sf::Vector2u pos, unsigned int oldGroundId, unsigned int newGroundId, Entities* entity, StateGame* state);

    ~GroundPlaceEvent();
    sf::Vector2u getPosition();
    unsigned int getNewGround();
    unsigned int getOldGround();
    Entities* getEntity();

protected:
    sf::Vector2u pos;
    unsigned int oldGroundId;
    unsigned int newGroundId;
    Entities* entity;
};




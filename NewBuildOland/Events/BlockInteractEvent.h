#pragma once
#include "GameEvent.h"
#include "SFML\System.hpp"

class BlockInteractEvent : public GameEvent
{
    public:
        BlockInteractEvent(sf::Vector2u pos, unsigned int block, Entities* entity, StateGame* state);
        virtual ~BlockInteractEvent();
        inline sf::Vector2u getPosition() { return position; };
        inline unsigned int getBlock() { return blockId; };
        inline Entities* getEntity() { return entit; };
    protected:
        sf::Vector2u position;
        unsigned int blockId;
        Entities* entit;
};



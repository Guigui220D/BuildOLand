#include "BlockInteractEvent.h"

BlockInteractEvent::BlockInteractEvent(sf::Vector2u pos, unsigned int block, Entities* entity, StateGame* state) : GameEvent(state)
{
    blockId = block;
    position = pos;
    entit = entity;
}

BlockInteractEvent::~BlockInteractEvent()
{
    //dtor
}

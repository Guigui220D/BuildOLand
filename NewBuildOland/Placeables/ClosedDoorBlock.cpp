#include "ClosedDoorBlock.h"

ClosedDoorBlock::ClosedDoorBlock(sf::IntRect textureRect, sf::IntRect faceRect)
    : Block(textureRect, "CLOSED_DOOR", sf::Color(135, 120, 60), true, true, faceRect)
{
    //ctor
}

ClosedDoorBlock::~ClosedDoorBlock()
{
    //dtor
}

void ClosedDoorBlock::onBlockInteract(BlockInteractEvent e)
{
    e.getState()->getWorld()->setBlockId(e.getPosition(), 8);
}

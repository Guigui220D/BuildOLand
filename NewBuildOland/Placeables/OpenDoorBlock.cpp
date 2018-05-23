#include "OpenDoorBlock.h"

OpenDoorBlock::OpenDoorBlock(sf::IntRect textureRect, sf::IntRect faceRect)
     : Block(textureRect, "OPEN_DOOR", sf::Color(135, 120, 60), false, true, faceRect)
{
    //ctor
}

OpenDoorBlock::~OpenDoorBlock()
{
    //dtor
}

void OpenDoorBlock::onBlockInteract(BlockInteractEvent e)
{
    e.getState()->getWorld()->setBlockId(e.getPosition(), 7);
}

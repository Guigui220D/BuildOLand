#include "TNTBlock.h"
#include <iostream>
#include "../Entities/TNTEntity.h"

TNTBlock::TNTBlock(sf::IntRect textureRect, sf::IntRect faceRect) : Block(textureRect, "TNT", sf::Color(255, 100, 100), true, true, faceRect)
{
    //ctor
}

TNTBlock::~TNTBlock()
{
    //dtor
}

void TNTBlock::onBlockInteract(BlockInteractEvent e)
{
    e.getState()->getWorld()->addEntity(new TNTEntity(e.getState()->getWorld(), e.getState()->getWorld()->getNextEntityId(), e.getPosition()));
    e.getState()->getWorld()->setBlockId(e.getPosition(), 0);
}

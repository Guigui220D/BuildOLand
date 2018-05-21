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

void TNTBlock::onBlockBreak(BlockBreakEvent e)
{
    sf::Vector2u pos = e.getPosition();
    e.getState()->getWorld()->addEntity(new TNTEntity(e.getState()->getWorld(), e.getPosition()));

}

Block *TNTBlock::getBlockOnBreak(StateGame *stateGame) {
    //Return nothing
    return nullptr;
}

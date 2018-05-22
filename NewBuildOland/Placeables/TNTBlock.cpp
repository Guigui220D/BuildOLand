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
    sf::Vector2u pos = e.getPosition();
    e.getState()->getWorld()->addEntity(new TNTEntity(e.getState()->getWorld(), e.getState()->getWorld()->getNextEntityId(), e.getPosition()));

}

void TNTBlock::onBlockBreak(BlockBreakEvent e) {
    sf::Vector2u pos = e.getPosition();
    e.getState()->getWorld()->addEntity(new TNTEntity(e.getState()->getWorld(), e.getState()->getWorld()->getNextEntityId(), e.getPosition()));
}

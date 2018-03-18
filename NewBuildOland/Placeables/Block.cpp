#include "stdafx.h"
#include "Block.h"


Block::Block(sf::IntRect textureRect, std::string name, sf::Color mapColor) : Placeable(textureRect, name, mapColor)
{
}


Block::~Block()
{
}

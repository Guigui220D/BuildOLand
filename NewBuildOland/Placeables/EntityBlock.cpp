#include "EntityBlock.h"


EntityBlock::EntityBlock(sf::IntRect textureRect, std::string name, sf::Color mapColor, bool hasHitbox, bool hasVolume, sf::IntRect side) : Block(textureRect, name, mapColor, hasHitbox, hasVolume, side)
{
	hasEntity = true;
}


EntityBlock::~EntityBlock()
{
}

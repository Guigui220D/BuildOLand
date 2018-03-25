#include "stdafx.h"
#include "Block.h"


Block::Block(sf::IntRect textureRect, std::string name, bool hasHitbox, sf::Color mapColor)
: Placeable(textureRect, name, mapColor)
, mHasHitbox(hasHitbox)
{
}


Block::~Block()
{
}

bool Block::hasHitbox() {
	return mHasHitbox;
}
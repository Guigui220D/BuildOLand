#include "stdafx.h"
#include "TestEntityBlock.h"


TestEntityBlock::TestEntityBlock(sf::IntRect rect) : Block(rect, "ENTITY_BLOCK", sf::Color::Green, true, false)
{
	hasEntity = true;
}


TestEntityBlock::~TestEntityBlock()
{
}

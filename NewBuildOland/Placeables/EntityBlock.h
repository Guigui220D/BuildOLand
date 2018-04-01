#pragma once
#include "Block.h"

class EntityBlock : public Block
{
public:
	EntityBlock(sf::IntRect textureRect, std::string name = "", sf::Color mapColor = sf::Color(255, 255, 255), bool hasHitbox = true, bool hasVolume = true, sf::IntRect side = sf::IntRect());
	~EntityBlock();
};


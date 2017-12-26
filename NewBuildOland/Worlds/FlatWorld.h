#pragma once
#include "World.h"

class FlatWorld : public World
{
public:
	FlatWorld();
	~FlatWorld();
	unsigned short getGround(sf::Vector2u pos) override;
	unsigned short getBlock(sf::Vector2u pos) override;
	void setGround(sf::Vector2u pos, unsigned short value) override;
	void setBlock(sf::Vector2u pos, unsigned short value) override;
};


#pragma once
#include "World.h"

class FlatWorld : public World
{
public:
	FlatWorld(Game& game);
	~FlatWorld();
	
	void generateWorld() override;

	unsigned short getGroundId(sf::Vector2u pos) override;
	unsigned short getBlockId(sf::Vector2u pos) override;
	void setGroundId(sf::Vector2u pos, unsigned short value) override;
	void setBlockId(sf::Vector2u pos, unsigned short value) override;

private:
};


#pragma once
#include "World.h"

class FlatWorld : public World
{
public:
	FlatWorld(StateGame& stateGame);
	~FlatWorld();

	void generateWorld(sf::Packet p = sf::Packet()) override;

private:
};


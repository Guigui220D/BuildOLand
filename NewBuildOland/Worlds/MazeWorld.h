#pragma once
#include "World.h"

class MazeWorld : public World
{
public:
	MazeWorld(StateGame& stateGame);
	~MazeWorld();

	void generateWorld(sf::Packet p = sf::Packet()) override;

private:
};


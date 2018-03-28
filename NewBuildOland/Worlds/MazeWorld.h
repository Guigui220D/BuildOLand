#pragma once
#include "World.h"

class MazeWorld : public World
{
public:
	MazeWorld(StateGame& stateGame);
	~MazeWorld();

	void generateWorld() override;

private:
};


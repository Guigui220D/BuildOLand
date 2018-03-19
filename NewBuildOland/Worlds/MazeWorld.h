#pragma once
#include "World.h"

class MazeWorld : public World
{
public:
	MazeWorld(Game& game);
	~MazeWorld();

	void generateWorld() override;

private:
};


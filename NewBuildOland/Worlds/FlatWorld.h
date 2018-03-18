#pragma once
#include "World.h"

class FlatWorld : public World
{
public:
	FlatWorld(Game& game);
	~FlatWorld();
	
	void generateWorld() override;

private:
};


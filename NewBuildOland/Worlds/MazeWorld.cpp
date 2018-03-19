#include "stdafx.h"
#include "MazeWorld.h"
#include "../States/StateGame.h"

MazeWorld::MazeWorld(Game& game)
	: World(game, "mazeworld")
{
	loadWorld();
	playerPos = sf::Vector2u(1, 1);
}


MazeWorld::~MazeWorld()
{
}

void MazeWorld::generateWorld() {
	//Set the world size
	worldSize = sf::Vector2u(50, 50);
	unsigned short const DEFAULT_GROUND = 3;
	unsigned short const DEFAULT_BLOCK = 0;
	
	for(int i = 0; i < worldSize.x * worldSize.y; i++) {
		groundIds.push_back(DEFAULT_GROUND);
		blockIds.push_back(DEFAULT_BLOCK);
	} 

	for(int x = 0; x < worldSize.x; x++) {
		for (int y = 0; y < worldSize.y; y++) {
			if(x % 2 == 0 && y % 2 == 0) {
				setBlockId(x, y, 2);
			}
		}
	}
}

#include "stdafx.h"
#include "MazeWorld.h"


MazeWorld::MazeWorld(Game& game)
	: World(game)
{
	loadWorld();
}


MazeWorld::~MazeWorld()
{
}

void MazeWorld::generateWorld() {
	//Set the world size
	worldSize = sf::Vector2u(50, 50);
	playerPos = sf::Vector2u(1, 1);

	unsigned int mapBlocks[60][60];
	unsigned int mapGrounds[60][60];

	for (unsigned int x = 0; x < worldSize.x; x++) {
		for (unsigned int y = 0; y < worldSize.y; y++) {

			mapGrounds[x][y] = 0;
			mapBlocks[x][y] = 0;
		}
	}

	for (unsigned int x = 0; x < worldSize.x; x += 2) {
		for (unsigned int y = 0; y < worldSize.y; y += 2) {

			mapGrounds[x][y] = 0;
			mapBlocks[x][y] = 0;
		}
	}

	for (unsigned int x = 0; x < worldSize.x; x++) {
		for (unsigned int y = 0; y < worldSize.y; y++) {

			groundIds.push_back(mapGrounds[x][y]);
			blockIds.push_back(mapBlocks[x][y]);
		}
	}
}

#include "FlatWorld.h"
#include <iostream>
#include "../Entities/StaticObjects/TestObject.h"


FlatWorld::FlatWorld(StateGame& stateGame)
	: World(stateGame, "flatworld")
{
	loadWorld();
	entities.push_back(new TestObject());
}


FlatWorld::~FlatWorld()
{
}

void FlatWorld::generateWorld() {
	//Set the world size
	worldSize = sf::Vector2u(24, 24);
	playerPos = sf::Vector2u(1, 1);
	//Populate the ground array
	for (unsigned int x = 0; x < worldSize.x; x++) {
		for (unsigned int y = 0; y < worldSize.y; y++) {

			groundIds.push_back((x % 2) + (y % 2));

		}
	}

	//Populate the block array
	for (unsigned int x = 0; x < worldSize.x; x++) {
		for (unsigned int y = 0; y < worldSize.y; y++) {

			if (x == 3) {
				blockIds.push_back(1);
			} else {
				blockIds.push_back(0);
			}

		}
	}

}

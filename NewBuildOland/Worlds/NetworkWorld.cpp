#include "NetworkWorld.h"
#include "../Utils/NetworkManager.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

NetworkWorld::NetworkWorld(StateGame& stateGame)
    : World(stateGame, "networkworld")
{
    generateWorld();
}

NetworkWorld::~NetworkWorld()
{
    //dtor
}

void NetworkWorld::generateWorld()
{
    std::cout << "Sending a request to get world data" << std::endl;
    if (!NetworkManager::askForWorld())
    {
        worldSize = sf::Vector2u(1, 1);
        playerPos = sf::Vector2u();
        groundIds.push_back(0);
        blockIds.push_back(0);
        std::cout << "Failed to ask for the world" << std::endl;
        return;
    }
    sf::Packet pack = NetworkManager::recieve();
    unsigned xsize, ysize;
    pack >> xsize >> ysize;
    worldSize = sf::Vector2u(xsize, ysize);
    playerPos = sf::Vector2u();

    for (int g = 0; g < xsize * ysize; g++) //Grounds
    {
        unsigned short val;
        pack >> val; //Get next short
        groundIds.push_back(val);
    }
    for (int b = xsize * ysize; b < xsize * ysize * 2; b++) //Blocks
    {
        unsigned short val;
        pack >> val; //Get next short
        blockIds.push_back(val);
    }


    //TEMPORARY
    /*
    for (unsigned int x = 0; x < worldSize.x; x++) {
		for (unsigned int y = 0; y < worldSize.y; y++) {

			groundIds.push_back((x % 2) + (y % 2));

		}
	}
	for (unsigned int x = 0; x < worldSize.x; x++) {
		for (unsigned int y = 0; y < worldSize.y; y++) {

			if (x == 3) {
				blockIds.push_back(1);
			} else {
				blockIds.push_back(0);
			}

		}
	}
	*/

}

//We don't want to save or load worlds because it's already stored on the server
bool NetworkWorld::loadWorld() {}
bool NetworkWorld::saveWorld() {}

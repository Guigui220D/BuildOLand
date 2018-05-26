#include "NetworkWorld.h"

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
    if (!getNetworkManager()->askForWorld())
    {
        worldSize = sf::Vector2u(1, 1);
        playerPos = sf::Vector2u();
        groundIds.push_back(0);
        blockIds.push_back(0);
        std::cout << "Failed to ask for the world" << std::endl;
        return;
    }
    sf::Packet pack = getNetworkManager()->syncReceive();
    unsigned xsize, ysize;
    pack >> xsize >> ysize;
    std::cout << "Size " << xsize << " by " << ysize << std::endl;
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



}

//We don't want to save or load worlds because it's already stored on the server
bool NetworkWorld::loadWorld() {}
bool NetworkWorld::saveWorld() {}

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

void NetworkWorld::generateWorld(sf::Packet p)
{
    //Clear the world
    groundIds.clear();
    blockIds.clear();
    //If packet is empty (default generation) create empty world
    if (p.getDataSize() == 0)
    {
        worldSize = sf::Vector2u(1, 1);
        playerPos = sf::Vector2u();
        groundIds.push_back(0);
        blockIds.push_back(0);
        //Ask for the world
        std::cout << "Sending a request to get world data" << std::endl;
        if (!getNetworkManager()->askForWorld())
        {
            std::cout << "Failed to ask for the world" << std::endl;
        }
        return;
    }
    else    //Else load from the packet
    {
        unsigned xsize, ysize;
        p >> xsize >> ysize;
        std::cout << "Received the world, size : " << xsize << " by " << ysize << std::endl;
        worldSize = sf::Vector2u(xsize, ysize);
        playerPos = sf::Vector2u();

        for (int g = 0; g < xsize * ysize; g++) //Grounds
        {
            unsigned short val;
            p >> val; //Get next short
            groundIds.push_back(val);
        }
        for (int b = 0; b < xsize * ysize; b++) //Blocks
        {
            unsigned short val;
            p >> val; //Get next short
            blockIds.push_back(val);
        }
        return;
    }
}

//We don't want to save or load worlds because it's already stored on the server
bool NetworkWorld::loadWorld() {}
bool NetworkWorld::saveWorld() {}

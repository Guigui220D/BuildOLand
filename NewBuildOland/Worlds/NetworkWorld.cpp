#include "NetworkWorld.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

NetworkWorld::NetworkWorld(StateGame& stateGame)
    : World(stateGame, "networkworld")
{

}

NetworkWorld::~NetworkWorld()
{
    //dtor
}

/*
void NetworkWorld::loadChunk(sf::Vector2i chunk)
{
    if (!isChunkLoaded(chunk))
    {

    }
}
*/

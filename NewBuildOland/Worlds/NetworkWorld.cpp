#include "NetworkWorld.h"

NetworkWorld::NetworkWorld(StateGame& stateGame)
    : World(stateGame, "networkworld")
{
    //ctor
}

NetworkWorld::~NetworkWorld()
{
    //dtor
}

void NetworkWorld::generateWorld()
{

}

//We don't want to save or load worlds because it's already stored on the server
bool NetworkWorld::loadWorld() {}
bool NetworkWorld::saveWorld() {}

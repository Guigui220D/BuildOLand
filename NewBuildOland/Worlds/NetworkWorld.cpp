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

void NetworkWorld::preDelete()
{
    loadedChunks.clear();
}

void NetworkWorld::loadChunk(sf::Vector2i chunk)
{
    if (!isChunkLoaded(chunk))
        loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), Chunk(chunk, false)));
    //TODO: Request the chunk's data
    std::cout << "TODO : Request chunk data.\n";
}

void NetworkWorld::unloadChunk(sf::Vector2i chunk, bool erase)
{
    //TODO: Manage entities on load and unload
    if (isChunkLoaded(chunk))
    {
        if (erase)
            loadedChunks.erase(loadedChunks.find(vector2iToInt64(chunk)));
        std::cout << "Unloaded chunk " << chunk.x << ", " << chunk.y << ".\n";
        return;
    }
    std::cout << "Tried to unload a chunk that wasn't loaded.\n";
}

void NetworkWorld::flushChunkCache() {};




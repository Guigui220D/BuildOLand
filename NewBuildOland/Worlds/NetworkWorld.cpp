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

void NetworkWorld::updateChunks(float delta)
{
    World::updateChunks(delta);
    if (clk.getElapsedTime().asSeconds() >= 1.f)
    {
        clk.restart();
        for (auto i = loadedChunks.begin(); i != loadedChunks.end(); i++)
        {
            if (!(*i).second.isReady())
                stateGame->getNetworkManager()->askForChunk((*i).second.getPosition());
        }
    }
}

void NetworkWorld::loadChunk(sf::Vector2i chunk)
{
    if (!isChunkLoaded(chunk))
        loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), Chunk(this, chunk, false)));
    stateGame->getNetworkManager()->askForChunk(chunk);
}

void NetworkWorld::unloadChunk(sf::Vector2i chunk, bool erase)
{
    //TODO: Manage entities on load and unload
    if (isChunkLoaded(chunk))
    {
        if (erase)
            loadedChunks.erase(loadedChunks.find(vector2iToInt64(chunk)));
        return;
    }
    std::cout << "Tried to unload a chunk that wasn't loaded.\n";
}

void NetworkWorld::handlePacket(sf::Packet p)
{
    int posX, posY;
    p >> posX >> posY;
    if (!isChunkLoaded(sf::Vector2i(posX, posY)))
        loadedChunks.emplace(std::make_pair(vector2iToInt64(sf::Vector2i(posX, posY)), Chunk(this, sf::Vector2i(posX, posY), false)));
    getChunk(sf::Vector2i(posX, posY))->handlePacket(p, sf::Vector2i(posX, posY));
}

void NetworkWorld::flushChunkCache() {};




#include "World.h"
#include "../Utils/FileManager.h"
#include "../Game.h"
#include "../States/StateBase.h"

#include <fstream>
#include <iostream>
#include <Windows.h>

World::World(StateGame& stateGame, std::string name)
	: stateGame(&stateGame)
{
	worldName = name;
}

unsigned short World::getBlockId(sf::Vector2i pos)
{
	//Temporary
	sf::Vector2i chunkPos = getChunkPosFromBlock(pos);
	//Check if chunk is loaded and load it
	if (!isChunkLoaded(chunkPos))
    {
        loadedChunks.emplace(std::make_pair(vector2iToInt64(chunkPos), Chunk(chunkPos)));
    }
    //Get the position of the block in the chunk
    sf::Vector2i blockPos(pos.x - chunkPos.x * Chunk::CHUNK_SIZE, pos.y - chunkPos.y * Chunk::CHUNK_SIZE);
    return getChunk(chunkPos)->getBlock(blockPos);
}

unsigned short World::getGroundId(sf::Vector2i pos)
{
	//Temporary
	sf::Vector2i chunkPos = getChunkPosFromBlock(pos);
	//Check if chunk is loaded and load it
	if (!isChunkLoaded(chunkPos))
    {
        loadedChunks.emplace(std::make_pair(vector2iToInt64(chunkPos), Chunk(chunkPos)));
    }
    //Get the position of the block in the chunk
    sf::Vector2i groundPos(pos.x - chunkPos.x * Chunk::CHUNK_SIZE, pos.y - chunkPos.y * Chunk::CHUNK_SIZE);
    return getChunk(chunkPos)->getGround(groundPos);
}

Block* World::getBlockAt(sf::Vector2i pos)
{
	return stateGame->getTileset()->getBlockById(getBlockId(pos));
}


void World::setGroundId(sf::Vector2i pos, unsigned short ground)
{
	//Temporary
	sf::Vector2i chunkPos = getChunkPosFromBlock(pos);
	//Check if chunk is loaded and load it
	if (!isChunkLoaded(chunkPos))
    {
        loadedChunks.emplace(std::make_pair(vector2iToInt64(chunkPos), Chunk(chunkPos)));
    }
    //Get the position of the block in the chunk
    sf::Vector2i groundPos(pos.x - chunkPos.x * Chunk::CHUNK_SIZE, pos.y - chunkPos.y * Chunk::CHUNK_SIZE);
    getChunk(chunkPos)->setGround(groundPos, ground);
}

void World::setBlockId(sf::Vector2i pos, unsigned short block)
{
	//Temporary
	sf::Vector2i chunkPos = getChunkPosFromBlock(pos);
	//Check if chunk is loaded and load it
	if (!isChunkLoaded(chunkPos))
    {
        loadedChunks.emplace(std::make_pair(vector2iToInt64(chunkPos), Chunk(chunkPos)));
    }
    //Get the position of the block in the chunk
    sf::Vector2i blockPos(pos.x - chunkPos.x * Chunk::CHUNK_SIZE, pos.y - chunkPos.y * Chunk::CHUNK_SIZE);
    getChunk(chunkPos)->setBlock(blockPos, block);
    sf::Vector2i rpos = getChunk(chunkPos)->getPosition();
}

World::~World()
{
    for (int i = 0; i < entities.size(); i++)
        delete(entities.at(i));
}

const std::vector<Entities *> &World::getEntities() const {
    return entities;
}

void World::removeEntitiesThatNeedToBeRemoved()
{
    int j = 0;
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities.at(i - j)->mustBeRemoved)
        {
            entities.erase(entities.begin() + (i - j));
            j++;
        }
    }
}

void World::removeEntityNowById(unsigned int id)
{
    for (auto i = entities.begin(); i < entities.end(); i++)
    {
        if ((*i)->getID() == id)
        {
            i = entities.erase(i);
        }
    }
}

void World::addEntity(Entities* entity)
{
    entities.push_back(entity);
}

Entities* World::getEntityById(unsigned int id)
{
    Entities* rep = nullptr;
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities.at(i)->getID() == id)
        {
            rep = entities.at(i);
            break;
        }
    }
    return rep;
}


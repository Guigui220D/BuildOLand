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

void World::loadChunk(sf::Vector2i chunk)
{
    if (!isChunkLoaded(chunk))
    {
        std::cout << "Loaded chunk " << chunk.x << ", " << chunk.y << ".\n";
        for (auto i = chunkCache.begin(); i != chunkCache.end(); i++)
        {
            if ((*i).chunk.getPosition() == chunk)
            {
                loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), (*i).chunk));
                for (auto j = (*i).entities.begin(); j < (*i).entities.end(); j++)
                {
                    Entities* e = (*j)->clone();
                    std::cout << "Added one entity: " << typeid(*e).name() << "\n";
                    entities.push_back(e);
                }
                for (auto j = (*i).entities.begin(); j < (*i).entities.end(); j++)
                    delete (*j);
                (*i).entities.clear();
                i = chunkCache.erase(i);
                return;
            }
        }
        //TODO: Try to load from disk
        //
        //
        //
        loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), Chunk(chunk)));
    }
}

void World::unloadChunk(sf::Vector2i chunk, bool erase)
{
    //When chunks are unloaded, they are not directly written on disk to avoid freezes, but instead are put in a cache that is ready to be saved
    if (isChunkLoaded(chunk))
    {
        CachedChunk cc;
        cc.chunk = *getChunk(chunk);
        sf::Vector2f chunkTopLeft(cc.chunk.getPosition().x * Chunk::CHUNK_SIZE * StateGame::TILE_SIZE, cc.chunk.getPosition().y * Chunk::CHUNK_SIZE * StateGame::TILE_SIZE);
        sf::Vector2f chunkBottomRight((cc.chunk.getPosition().x + 1) * Chunk::CHUNK_SIZE * StateGame::TILE_SIZE, (cc.chunk.getPosition().y + 1) * Chunk::CHUNK_SIZE * StateGame::TILE_SIZE);
        for (auto i = entities.begin(); i < entities.end(); i++)
        {
            if ((*i)->getPosition().x >= chunkTopLeft.x && (*i)->getPosition().x <= chunkBottomRight.x
                && (*i)->getPosition().y >= chunkTopLeft.y && (*i)->getPosition().y <= chunkBottomRight.y)
            {
                Entities* e = (*i)->clone();
                std::cout << "Removed one entity: " << typeid(*e).name() << "\n";
                cc.entities.push_back(e);
                delete (*i);
                i = entities.erase(i);
            }
        }
        chunkCache.push_back(cc);
        if (erase)
            loadedChunks.erase(loadedChunks.find(vector2iToInt64(chunk)));
        std::cout << "Unloaded chunk " << chunk.x << ", " << chunk.y << ".\n";
        return;
    }
    std::cout << "Tried to unload a chunk that wasn't loaded.\n";
}

void World::flushChunkCache()
{
    //TODO: Save chunks to disk
    //Iterate through chunks cache and save chunks one by one
    //
    //
    std::cout << "Saved chunk cache, " << chunkCache.size() << " chunks!\n";
    chunkCache.clear();
}

void World::updateChunks()
{
    std::vector<sf::Vector2i> toUnload;
    for (auto i = loadedChunks.begin(); i != loadedChunks.end(); i++)
    {
        sf::Vector2i pos = (*i).second.getPosition();
        //Get center of chunk
        sf::Vector2f center(pos.x * Chunk::CHUNK_SIZE + Chunk::CHUNK_SIZE / 2, pos.y * Chunk::CHUNK_SIZE + Chunk::CHUNK_SIZE / 2);
        //calculate player's distance to chunk
        sf::Vector2f delta = center - stateGame->getPlayer()->getWorldPos();
        delta = sf::Vector2f(abs(delta.x), abs(delta.y));
        if (delta.x > UNLOAD_DISTANCE || delta.y > UNLOAD_DISTANCE)
        {
            toUnload.push_back(pos);
        }
    }
    for (unsigned int i = 0; i < toUnload.size(); i++)
        unloadChunk(toUnload.at(i), true);
}

unsigned short World::getBlockId(sf::Vector2i pos)
{
	//Temporary
	sf::Vector2i chunkPos = getChunkPosFromBlock(pos);
	//Check if chunk is loaded and load it
	if (!isChunkLoaded(chunkPos))
    {
        loadChunk(chunkPos);
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
        loadChunk(chunkPos);
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
        loadChunk(chunkPos);
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
        loadChunk(chunkPos);
    }
    //Get the position of the block in the chunk
    sf::Vector2i blockPos(pos.x - chunkPos.x * Chunk::CHUNK_SIZE, pos.y - chunkPos.y * Chunk::CHUNK_SIZE);
    getChunk(chunkPos)->setBlock(blockPos, block);
}

World::~World()
{
    for (auto i = loadedChunks.begin(); i != loadedChunks.end(); i++)
        unloadChunk((*i).second.getPosition(), false);
    loadedChunks.clear();
    flushChunkCache();
    for (unsigned int i = 0; i < entities.size(); i++)
        delete(entities.at(i));
}

const std::vector<Entities*> &World::getEntities() const
{
    return entities;
}

void World::removeEntitiesThatNeedToBeRemoved()
{
    for (auto i = entities.begin(); i < entities.end(); i++)
    {
        if ((*i)->mustBeRemoved)
        {
            delete (*i);
            i = entities.erase(i);
        }
    }
}

void World::removeEntityNowById(unsigned int id)
{
    for (auto i = entities.begin(); i < entities.end(); i++)
    {
        if ((*i)->getID() == id)
        {
            delete (*i);
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
    for (unsigned int i = 0; i < entities.size(); i++)
    {
        if (entities.at(i)->getID() == id)
        {
            rep = entities.at(i);
            break;
        }
    }
    return rep;
}


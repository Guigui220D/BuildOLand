#include "World.h"
#include "../Utils/FileManager.h"
#include "../Game.h"
#include "../States/StateBase.h"

#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <sys/stat.h>

World::World(StateGame& stateGame, std::string name)
	: stateGame(&stateGame)
{
	worldName = name;
}

void World::loadChunk(sf::Vector2i chunk)
{
    if (!isChunkLoaded(chunk))
    {
        std::cout << "Load chunk " << chunk.x << ", " << chunk.y << ".\n";
        //Looking in cached chunks to see if it's already there
        for (auto i = chunkCache.begin(); i != chunkCache.end(); i++)
        {
            if ((*i).chunk.getPosition() == chunk)
            {
                loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), (*i).chunk));
                //Load entities
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
        //If it's not, load from disk
        std::string const chunkFileName("./gamedata/worlds/" + worldName + "/" + std::to_string(chunk.x) + "_" + std::to_string(chunk.y) + ".chunk");
        //Check if the file exists
        struct stat buffer; //???
        if (stat(chunkFileName.c_str(), &buffer) == 0)
        {
            std::ifstream chunkFile(chunkFileName.c_str(), std::ios::binary | std::ios::in);
            if(chunkFile.is_open()) {
                //The file exists, we can read it now
                //Get the size
                chunkFile.seekg(0, chunkFile.end);
                int fileSize = chunkFile.tellg();
                //Get the data
                chunkFile.seekg(0, chunkFile.beg);
                char* buffer = new char[fileSize];
                chunkFile.read(buffer, fileSize);
                std::vector<unsigned char> data;
                for (int i = 0; i < fileSize; i++)
                {
                    data.push_back((unsigned char)buffer[i]);
                }
                delete buffer;
                if (chunkFile)
                {
                    loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), Chunk(data, chunk)));
                    std::cout << "Loaded chunk from disk.\n";
                    chunkFile.close();
                    return;
                }
                else
                    std::cout << "Could not read chunk from file.\n";
                chunkFile.close();
            }
        }
        //The chunk doesn't exist, generate it
        loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), Chunk(chunk)));
        generateChunk(*getChunk(chunk), Generators::SandGrassPattern1);
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
        //Store entities
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
    bool success = true;
    //Iterate through chunks to save them
    for (unsigned int i = 0; i < chunkCache.size(); i++)
    {
        std::vector<unsigned char> data = chunkCache.at(i).getData();
        std::string const chunkFileName("./gamedata/worlds/" + worldName + "/" + std::to_string(chunkCache.at(i).chunk.getPosition().x) + "_" + std::to_string(chunkCache.at(i).chunk.getPosition().y) + ".chunk");
        //Save the chunk
        std::ofstream chunkFileFlux(chunkFileName.c_str(), std::ios::binary | std::ios::out);
        if (!chunkFileFlux.is_open())
            FileManager::createFolder("./gamedata/worlds/" + worldName + "/");

        if (chunkFileFlux) {
            //Everything okay, writing
            chunkFileFlux.write(reinterpret_cast<char*>(data.data()), data.size());
            chunkFileFlux.close();
        }
        else {
            std::cout << "Could not save a chunk! Giving up.\n";
            success = false;
            break;
        }

    }
    if (success)
    {
        std::cout << "Saved chunk cache, " << chunkCache.size() << " chunks!\n";
        chunkCache.clear();
    }
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

void World::generateChunk(Chunk& chunk, Generators gen)
{
    switch (gen)
    {
    case Generators::SandGrassPattern1:
        for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
        {
            for (int y = 0; y < Chunk::CHUNK_SIZE; y++)
            {
                if ((x + y) % 2 && (x + y) % 3)
                    chunk.setGround(sf::Vector2i(x, y), 1);
            }
        }
        break;
    }
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


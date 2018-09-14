#include "World.h"
#include "../Utils/FileManager.h"
#include "../Game.h"
#include "../States/StateBase.h"
#include "../Entities/BlackWarrior.h"
#include "../Entities/TNTEntity.h"

#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <sys/stat.h>

World::World(StateGame& stateGame, std::string name)
	: stateGame(&stateGame)
{
	worldName = name;

	{
	    BlackWarrior* warrior = new BlackWarrior(this, getNextEntityId());
        warrior->init(2, 1);
        addEntity(warrior);
	}
}

void World::loadChunk(sf::Vector2i chunk)
{
    if (!isChunkLoaded(chunk))
    {
        //std::cout << "Load chunk " << chunk.x << ", " << chunk.y << "\n";
        //Looking in cached chunks to see if it's already there
        for (auto i = chunkCache.begin(); i != chunkCache.end(); )
        {
            if ((*i).chunk->getPosition() == chunk)
            {
                loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), (*i).chunk));
                for (auto j = (*i).entities.begin(); j < (*i).entities.end(); j++)
                {
                    addEntity(*j);
                }
                (*i).entities.clear();
                i = chunkCache.erase(i);
                return;
            }
            else
                i++;
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
                    loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), ChunkPtr(new Chunk(this, data, chunk))));
                    //Process entities data on the remaining bytes
                    {
                        //Get entity count
                        union
                        {
                            int i;
                            unsigned char bytes[4];
                        } ecount;
                        for (int i = 0; i < 4; i++)
                        {
                            ecount.bytes[i] = data.at(0);
                            data.erase(data.begin());
                        }
                        if (ecount.i)
                            std::cout << "Entity count : " << ecount.i << '\n';
                        //Get all entities
                        for (int i = 0; i < ecount.i; i++)
                        {
                            //Get the code
                            union
                            {
                                int i;
                                unsigned char bytes[4];
                            } codeu;
                            for (int i = 0; i < 4; i++)
                            {
                                codeu.bytes[i] = data.at(0);
                                data.erase(data.begin());
                            }
                            //Get position
                            union
                            {
                                float f;
                                unsigned char bytes[4];
                            } posx;
                            union
                            {
                                float f;
                                unsigned char bytes[4];
                            } posy;
                            for (int i = 0; i < 4; i++)
                            {
                                posx.bytes[i] = data.at(0);
                                data.erase(data.begin());
                            }
                            for (int i = 0; i < 4; i++)
                            {
                                posy.bytes[i] = data.at(0);
                                data.erase(data.begin());
                            }
                            //Get more data if needed and instantiate entity
                            switch (codeu.i)
                            {
                            case EntityCodes::blackWarrior:
                                {
                                    {
                                        BlackWarrior* warrior = new BlackWarrior(this, getNextEntityId());
                                        warrior->init(posx.f / StateGame::TILE_SIZE, posy.f / StateGame::TILE_SIZE);
                                        warrior->setDirection(data.at(0));
                                        addEntity(warrior);
                                    }
                                }
                                data.erase(data.begin());
                                break;
                            case EntityCodes::tnt:
                                {
                                    {
                                        TNTEntity* te = new TNTEntity(this, getNextEntityId(), sf::Vector2i(posx.f / StateGame::TILE_SIZE, posy.f / StateGame::TILE_SIZE));
                                        addEntity(te);
                                    }
                                }
                                break;
                            }
                        }
                    }
                    chunkFile.close();
                    return;
                }
                else
                    std::cout << "Could not read chunk from file.\n";
                chunkFile.close();
            }
        }
        //The chunk doesn't exist, generate it
        loadedChunks.emplace(std::make_pair(vector2iToInt64(chunk), ChunkPtr(new Chunk(this, chunk))));
        generateChunk(getChunk(chunk), Generators::SandGrassPattern1);
    }
}

void World::unloadChunk(sf::Vector2i chunk, bool erase)
{
    //When chunks are unloaded, they are not directly written on disk to avoid freezes, but instead are put in a cache that is ready to be saved
    if (isChunkLoaded(chunk))
    {
        CachedChunk cc;
        cc.chunk = getChunk(chunk);
        sf::Vector2f chunkTopLeft(cc.chunk->getPosition().x * Chunk::CHUNK_SIZE * StateGame::TILE_SIZE, cc.chunk->getPosition().y * Chunk::CHUNK_SIZE * StateGame::TILE_SIZE);
        sf::Vector2f chunkBottomRight((cc.chunk->getPosition().x + 1) * Chunk::CHUNK_SIZE * StateGame::TILE_SIZE, (cc.chunk->getPosition().y + 1) * Chunk::CHUNK_SIZE * StateGame::TILE_SIZE);
        //Store entities
        for (auto i = entities.begin(); i < entities.end(); )
        {
            if ((*i)->getPosition().x >= chunkTopLeft.x && (*i)->getPosition().x <= chunkBottomRight.x
                && (*i)->getPosition().y >= chunkTopLeft.y && (*i)->getPosition().y <= chunkBottomRight.y)
            {
                cc.entities.push_back(*i);
                i = entities.erase(i);
            }
            else
                i++;
        }
        if (!cc.chunk->isReady())
        {
            std::cout << "Cannot cache a chunk that is not ready.\n";
            return;
        }
        chunkCache.push_back(cc);
        if (erase)
            loadedChunks.erase(loadedChunks.find(vector2iToInt64(chunk)));
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
        std::string const chunkFileName("./gamedata/worlds/" + worldName + "/" + std::to_string(chunkCache.at(i).chunk->getPosition().x) + "_" + std::to_string(chunkCache.at(i).chunk->getPosition().y) + ".chunk");
        //Save the chunk
        std::ofstream chunkFileFluxTest(chunkFileName.c_str(), std::ios::binary | std::ios::out);
        if (!chunkFileFluxTest.is_open())
        {
            FileManager::createFolder("./gamedata/worlds/" + worldName + "/");
        }
        chunkFileFluxTest.close();

        std::ofstream chunkFileFlux(chunkFileName.c_str(), std::ios::binary | std::ios::out);

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
        chunkCache.clear();
}

void World::updateChunks(float delta)
{
    std::vector<sf::Vector2i> toUnload;
    for (auto i = loadedChunks.begin(); i != loadedChunks.end(); i++)
    {
        (*i).second->updateTileEntities(delta);
        sf::Vector2i pos = (*i).second->getPosition();
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
    if (chunkCache.size() >= 32)
        flushChunkCache();
}

void World::generateChunk(ChunkPtr chunk, Generators gen)
{
    switch (gen)
    {
    case Generators::SandGrassPattern1:
        for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
        {
            for (int y = 0; y < Chunk::CHUNK_SIZE; y++)
            {
                if ((x + y) % 2 && (x + y) % 3)
                    chunk->setGround(sf::Vector2i(x, y), 1);
            }
        }
        break;
    }
}

std::shared_ptr<Chunk> World::pgetChunk(sf::Vector2i chunk)
{
    loadChunk(chunk);
    return getChunk(chunk);
}

unsigned short World::getBlockId(sf::Vector2i pos, const bool load)
{
	sf::Vector2i chunkPos = getChunkPosFromBlock(pos);
	//Check if chunk is loaded and load it
	if (!load && !isChunkLoaded(chunkPos))
        return 0;
    loadChunk(chunkPos);
    //Get the position of the block in the chunk
    sf::Vector2i blockPos(pos.x - chunkPos.x * Chunk::CHUNK_SIZE, pos.y - chunkPos.y * Chunk::CHUNK_SIZE);
    return getChunk(chunkPos)->getBlock(blockPos);
}

unsigned short World::getGroundId(sf::Vector2i pos, const bool load)
{
	sf::Vector2i chunkPos = getChunkPosFromBlock(pos);
	//Check if chunk is loaded and load it
	if (!load && !isChunkLoaded(chunkPos))
        return 0;
    loadChunk(chunkPos);
    //Get the position of the block in the chunk
    sf::Vector2i groundPos(pos.x - chunkPos.x * Chunk::CHUNK_SIZE, pos.y - chunkPos.y * Chunk::CHUNK_SIZE);
    return getChunk(chunkPos)->getGround(groundPos);
}

Block* World::getBlockAt(sf::Vector2i pos, const bool load)
{
	return stateGame->getTileset()->getBlockById(getBlockId(pos, load));
}

void World::setGroundId(sf::Vector2i pos, unsigned short ground)
{
	sf::Vector2i chunkPos = getChunkPosFromBlock(pos);
	//Check if chunk is loaded and load it
    loadChunk(chunkPos);
    //Get the position of the block in the chunk
    sf::Vector2i groundPos(pos.x - chunkPos.x * Chunk::CHUNK_SIZE, pos.y - chunkPos.y * Chunk::CHUNK_SIZE);
    getChunk(chunkPos)->setGround(groundPos, ground);
}

void World::setBlockId(sf::Vector2i pos, unsigned short block)
{
	sf::Vector2i chunkPos = getChunkPosFromBlock(pos);
	//Check if chunk is loaded and load it
    loadChunk(chunkPos);
    //Get the position of the block in the chunk
    sf::Vector2i blockPos(pos.x - chunkPos.x * Chunk::CHUNK_SIZE, pos.y - chunkPos.y * Chunk::CHUNK_SIZE);
    getChunk(chunkPos)->setBlock(blockPos, block);
}

World::~World()
{
    for (unsigned int i = 0; i < entities.size(); i++)
        delete(entities.at(i));
}

void World::preDelete()
{
    for (auto i = loadedChunks.begin(); i != loadedChunks.end(); i++)
        unloadChunk((*i).second->getPosition(), false);
    loadedChunks.clear();
    flushChunkCache();
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
    for (auto i = entities.begin(); i < entities.end(); )
    {
        if ((*i)->getID() == id)
        {
            delete (*i);
            i = entities.erase(i);
        }
        else
            i++;
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

void World::handlePacket(sf::Packet p) { }


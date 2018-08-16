#pragma once
#include <SFML\system.hpp>
#include <SFML\Network.hpp>
#include <unordered_map>
#include "../Utils/TileSet.h"
#include "../Placeables/Block.h"
#include "Chunk.h"
#include "CachedChunk.h"
#include <math.h>

class Entities;

class StateGame;

class World
{
public:
    static const int UNLOAD_DISTANCE = 32;

	World(StateGame& stateGame, std::string name = "world");
	virtual ~World();

	unsigned short getGroundId(sf::Vector2i pos);
	unsigned short getBlockId(sf::Vector2i pos);
	Block* getBlockAt(sf::Vector2i pos);
	void setGroundId(sf::Vector2i pos, unsigned short ground);
	void setBlockId(sf::Vector2i pos, unsigned short block);

	inline std::string getName() { return worldName; };

	inline StateGame* getStateGame() { return stateGame; };

	const std::vector<Entities*> &getEntities() const;
    virtual void addEntity(Entities* entity);
	virtual void removeEntitiesThatNeedToBeRemoved();
	virtual void removeEntityNowById(unsigned int id);
	inline unsigned int getNextEntityId() { return ++nextEntityId; };
    Entities* getEntityById(unsigned int id);

    virtual void updateChunks();
    virtual void loadChunk(sf::Vector2i chunk);
    virtual void unloadChunk(sf::Vector2i chunk, bool erase);
    virtual void flushChunkCache();

    //Chunks (Should be private, temporary public for chunk map
	std::map<uint64_t, Chunk> loadedChunks;
	std::vector<CachedChunk> chunkCache;

	//Call for telling the other methods that the world is deleted
	inline void setDeleted() { isBeingDeleted = true; };

protected:
	StateGame* stateGame = nullptr;

	long worldSeed;
	std::string worldName;

	std::vector<Entities*> entities;



    inline sf::Vector2i getChunkPosFromBlock(sf::Vector2i block)
        { return sf::Vector2i((int)floor((double)block.x / Chunk::CHUNK_SIZE), (int)floor((double)block.y / Chunk::CHUNK_SIZE)); };
    inline bool isChunkLoaded(sf::Vector2i chunkPos) { return loadedChunks.find(vector2iToInt64(chunkPos)) != loadedChunks.end(); };
    inline Chunk* getChunk(sf::Vector2i chunkPos) { return &((*loadedChunks.find(vector2iToInt64(chunkPos))).second); };
    inline uint64_t vector2iToInt64(sf::Vector2i vec)
        {
            uint64_t lon = vec.x;
            lon <<= 32;
            lon |= 0xFFFFFFFF & vec.y;
            return lon;
        };

private:
	bool isBeingDeleted = false;

	unsigned int nextEntityId = 0;

};


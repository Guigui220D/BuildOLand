#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <queue>

#include "../../TileEntities/TileEntities.h"

class World;

class Chunk
{
    public:
        //One chunk is 16 blocks
        static const int CHUNK_SIZE = 16;

        Chunk(World* world, sf::Vector2i chunkPos, bool rdy = true);
        Chunk(World* world);
        Chunk();    //Should not be called (only for CachedChunk's empty constructor
        //Load a chunk
        Chunk(World* world, std::queue<unsigned char>& data, sf::Vector2i chunkPos);
        virtual ~Chunk();

        void handlePacket(sf::Packet p, sf::Vector2i pos);

        void setBlock(sf::Vector2i pos, unsigned short block);
        void setGround(sf::Vector2i pos, unsigned short ground);
        unsigned short getBlock(sf::Vector2i pos);
        unsigned short getGround(sf::Vector2i pos);
        TileEntities* getEntity(sf::Vector2i pos);

        inline sf::Vector2i getPosition() { return position; };
        inline bool isReady() { return ready; };

        void updateTileEntities(float delta);

        inline World* getWorld() { return world; };

    private:
        //The position of the chunk, not to confuse with the position of the blocks
        sf::Vector2i position;
        //Works like old worlds
        std::vector<unsigned short> blocks;
        std::vector<unsigned short> grounds;
        std::vector<TileEntities*> blockEntities;

        bool ready = false;

        World* world;

};


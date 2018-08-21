#pragma once
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>

class Chunk
{
    public:
        //One chunk is 16 blocks
        static const int CHUNK_SIZE = 16;

        Chunk(sf::Vector2i chunkPos, bool rdy = true);
        Chunk();
        //Load a chunk
        Chunk(std::vector<unsigned char>& data, sf::Vector2i chunkPos);
        virtual ~Chunk();

        void handlePacket(sf::Packet p, sf::Vector2i pos);

        void setBlock(sf::Vector2i pos, unsigned short block);
        void setGround(sf::Vector2i pos, unsigned short ground);
        unsigned short getBlock(sf::Vector2i pos);
        unsigned short getGround(sf::Vector2i pos);

        inline sf::Vector2i getPosition() { return position; };
        inline bool isReady() { return ready; };

    private:
        //The position of the chunk, not to confuse with the position of the blocks
        sf::Vector2i position;
        //Works like old worlds
        std::vector<unsigned short> blocks;
        std::vector<unsigned short> grounds;

        bool ready;
};


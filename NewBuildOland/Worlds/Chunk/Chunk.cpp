#include "Chunk.h"
#include <iostream>

Chunk::Chunk(sf::Vector2i chunkPos)
{
    position = chunkPos;
    //Fill array
    for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
    {
        grounds.push_back(0);
        blocks.push_back(0);
    }
}

Chunk::Chunk() {}

Chunk::Chunk(std::vector<unsigned char>& data, sf::Vector2i chunkPos)
{
    //We remove all block data, the rest, entities data, is kept for the world
    int posX, posY;
    //Get pos x and pos y
    posX = (int)((int)(data.at(0)) | (int)(data.at(1)) << 8 | (int)(data.at(2)) << 16 | (int)(data.at(3)) << 24);
    data.erase(data.begin(), data.begin() + 4);
    posY = (int)(data.at(0) | data.at(1) << 8 | data.at(2) << 16 | data.at(3) << 24);
    data.erase(data.begin(), data.begin() + 4);
    position = sf::Vector2i(posX, posY);
    if (chunkPos != position)   //As a security
    {
        std::cout << "Failed to load chunk from disk. Got chunk " << position.x << ", " << position.y << ".\n";
        position = chunkPos;
        for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
        {
            blocks.push_back((unsigned short)0);
            grounds.push_back((unsigned short)0);
        }
    }
    else
    {
        //Get grounds
        for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE * 2); i += 2)
        {
            grounds.push_back(data.at(i) | data.at(i + 1) << 8);
        }
        data.erase(data.begin(), data.begin() + (CHUNK_SIZE * CHUNK_SIZE * 2));
        //Then blocks
        for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE * 2); i += 2)
        {
            blocks.push_back(data.at(i) | data.at(i + 1) << 8);
        }
        data.erase(data.begin(), data.begin() + (CHUNK_SIZE * CHUNK_SIZE * 2));
        std::cout << "Loaded chunk " << position.x << ", " << position.y << " successfully from disk.\n";
    }
}

Chunk::~Chunk()
{
    //dtor
}

void Chunk::setBlock(sf::Vector2i pos, unsigned short block)
{
    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE)
    return;

    blocks[pos.x + pos.y * CHUNK_SIZE] = block;
}

void Chunk::setGround(sf::Vector2i pos, unsigned short ground)
{
    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE)
    return;

    grounds[pos.x + pos.y * CHUNK_SIZE] = ground;
}

unsigned short Chunk::getBlock(sf::Vector2i pos)
{
    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE)
    return 0;

    return blocks.at(pos.x + pos.y * CHUNK_SIZE);
}

unsigned short Chunk::getGround(sf::Vector2i pos)
{
    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE)
    return 0;

    return grounds.at(pos.x + pos.y * CHUNK_SIZE);
}

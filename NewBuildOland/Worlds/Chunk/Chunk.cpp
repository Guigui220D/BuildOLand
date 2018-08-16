#include "Chunk.h"

Chunk::Chunk(sf::Vector2i chunkPos)
{
    position = chunkPos;
    for (int i = 0; i < (16 * 16); i++)
    {
        if (i == 0 || i == (16 * 16 - 1))
        {
            blocks.push_back((unsigned short)6);
        }
        else
        {
            blocks.push_back((unsigned short)0);
        }
        grounds.push_back((unsigned short)(i % 3));
    }
}

Chunk::Chunk() {}

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

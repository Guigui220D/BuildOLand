#include "Chunk.h"
#include <iostream>
#include "../Entities/EntityCodes.h"
#include "../Worlds/World.h"
#include "../../States/StateGame.h"

#include "../../TileEntities/BlinkerTileE.h"

Chunk::Chunk(World* world, sf::Vector2i chunkPos, bool rdy) : world(world)
{
    position = chunkPos;
    ready = rdy;
    //Fill array
    for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
    {
        grounds.push_back(0);
        blocks.push_back(0);
        blockEntities.push_back(nullptr);
    }
}

Chunk::Chunk(World* world) : world(world) { ready = false; }

Chunk::Chunk() {}

Chunk::Chunk(World* world, std::vector<unsigned char>& data, sf::Vector2i chunkPos) : world(world)
{
    ready = false;
    //Check the size of the data
    if (data.size() < CHUNK_SIZE * CHUNK_SIZE * 2)
    {
        std::cout << "Could not load chunk " << chunkPos.x << ", " << chunkPos.y << " (invalid data size).\n";
        return;
    }
    //We remove all block data, the rest, entities data, is kept for the world
    int posX, posY;
    //Get pos x and pos y
    posX = (int)((int)(data.at(0)) | (int)(data.at(1)) << 8 | (int)(data.at(2)) << 16 | (int)(data.at(3)) << 24);
    data.erase(data.begin(), data.begin() + 4);
    posY = (int)(data.at(0) | data.at(1) << 8 | data.at(2) << 16 | data.at(3) << 24);
    data.erase(data.begin(), data.begin() + 4);
    position = sf::Vector2i(posX, posY);
    if (chunkPos == position)   //Check the position
    {
        for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
            blockEntities.push_back(nullptr);
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
        ready = true;
    }
    else
    {
        std::cout << "Could not load chunk " << chunkPos.x << ", " << chunkPos.y << " (invalid position).\n";
    }
}

void Chunk::handlePacket(sf::Packet p, sf::Vector2i pos)
{
    grounds.clear();
    blocks.clear();
    position = pos;
    unsigned short ground, block;
    for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
    {
        p >> ground;
        grounds.push_back(ground);
        blockEntities.push_back(nullptr);
    }
    for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
    {
        p >> block;
        blocks.push_back(block);
    }
    ready = true;
}

Chunk::~Chunk()
{
    /*
    for (auto i = blockEntities.begin(); i < blockEntities.end(); i++)
        delete (blockEntities);
        */
}

void Chunk::setBlock(sf::Vector2i pos, unsigned short block)
{
    if (!ready)
        return;

    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE)
    return;

    delete blockEntities[pos.x + pos.y * CHUNK_SIZE];
    blockEntities[pos.x + pos.y * CHUNK_SIZE] = nullptr;
    blocks[pos.x + pos.y * CHUNK_SIZE] = block;
    switch (world->getStateGame()->getTileset()->getBlockById(block)->getTileEntity())
    {
    case TileEntityCodes::blinker:
        blockEntities[pos.x + pos.y * CHUNK_SIZE] = new BlinkerTileE(world, sf::Vector2i(position.x * CHUNK_SIZE + pos.x, position.y * CHUNK_SIZE + pos.y));
        break;
    case TileEntityCodes::none:
    default:
        break;
    }
}

void Chunk::setGround(sf::Vector2i pos, unsigned short ground)
{
    if (!ready)
        return;

    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE)
    return;

    grounds[pos.x + pos.y * CHUNK_SIZE] = ground;
}

unsigned short Chunk::getBlock(sf::Vector2i pos)
{
    if (!ready)
        return 0;

    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE)
    return 0;

    return blocks.at(pos.x + pos.y * CHUNK_SIZE);
}

unsigned short Chunk::getGround(sf::Vector2i pos)
{
    if (!ready)
        return 0;

    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE)
    return 0;

    return grounds.at(pos.x + pos.y * CHUNK_SIZE);
}

void Chunk::updateTileEntities(float delta)
{
    for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
    {
        if (blockEntities.at(i) != nullptr)
            blockEntities.at(i)->update(delta);
    }
}

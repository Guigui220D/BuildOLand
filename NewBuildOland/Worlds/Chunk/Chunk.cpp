#include "Chunk.h"
#include <iostream>
#include "../../Entities/EntityCodes.h"
#include "../World.h"
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

Chunk::Chunk() { }

Chunk::Chunk(World* world, unsigned char*& dataPtr, sf::Vector2i chunkPos) : world(world)
{
    //We load the data from a pointer (dataPtr) and increment the it each time
    ready = false;
    //Check the size of the data
    /* TODO : To move to the world class
    if (data.size() < CHUNK_SIZE * CHUNK_SIZE * 2 + 1)
    {
        std::cout << "Could not load chunk " << chunkPos.x << ", " << chunkPos.y << " (invalid data size).\n";
        return;
    }
    */
    //Get pos x and pos y
    memcpy(&position, dataPtr, sizeof(sf::Vector2f));
    dataPtr += sizeof(sf::Vector2f);

    if (chunkPos == position)   //Check the position
    {
        //Get grounds
        /*
        for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
        {
            unsigned char a = data.front();
            data.pop();
            grounds.push_back(a | data.front() << 8);
            data.pop();
        */
        grounds = std::vector<unsigned short>(CHUNK_SIZE * CHUNK_SIZE);
        memcpy(grounds.data(), dataPtr, (CHUNK_SIZE * CHUNK_SIZE * sizeof(short)));
        dataPtr += (CHUNK_SIZE * CHUNK_SIZE * sizeof(short));
        //Then blocks
        unsigned char blockEntityCount = 0;
        std::vector<TileEntities*> tentities;

        blocks = std::vector<unsigned short>(CHUNK_SIZE * CHUNK_SIZE);
        memcpy(blocks.data(), dataPtr, (CHUNK_SIZE * CHUNK_SIZE * sizeof(short)));
        dataPtr += (CHUNK_SIZE * CHUNK_SIZE * sizeof(short));

        for (int y = 0; y < CHUNK_SIZE; y++)
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            unsigned short id = blocks[x + y * CHUNK_SIZE];
            TileEntityCodes codes = world->getStateGame()->getTileset()->getBlockById(id)->getTileEntity();
            blockEntityCount++;
            //Add block entity if needed
            switch (codes)
            {
            case TileEntityCodes::blinker:
                {
                    BlinkerTileE* e = new BlinkerTileE(world, sf::Vector2i(x + position.x * CHUNK_SIZE, y + position.y * CHUNK_SIZE));
                    blockEntities.push_back(e);
                    tentities.push_back(e);
                }
                break;
            case TileEntityCodes::none:
                blockEntityCount--;
                blockEntities.push_back(nullptr);
                break;
            }
        }
        //Get block entity count, to check
        {
            unsigned char fileBlockEntityCount = *dataPtr++;
            if (fileBlockEntityCount != blockEntityCount || tentities.size() != fileBlockEntityCount)
            {
                std::cout << "Failed to load chunk " << chunkPos.x << ", " << chunkPos.y << ", didn't load tile entities (count doesn't match).\n";
                return;
            }
            if (fileBlockEntityCount)
                std::cout << "Loading " << (int)fileBlockEntityCount << " tile entities\n";
            //Load data about each blockentity
            for (TileEntities* te : tentities)
            {
                unsigned int dataSize;
                memcpy(&dataSize, dataPtr, sizeof(int));
                dataPtr += sizeof(int);

                std::vector<unsigned char> teData(dataSize);
                memcpy(teData.data(), dataPtr, dataSize);
                dataPtr += dataSize;
                te->takeData(teData);
            }
        }
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
    for (unsigned int i = 0; i < blockEntities.size(); i++)
    {
        if (blockEntities.at(i) != nullptr)
            delete blockEntities.at(i);
    }
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

TileEntities* Chunk::getEntity(sf::Vector2i pos)
{
    if (!ready)
        return nullptr;

    if (pos.x < 0 || pos.y < 0 ||
        pos.x >= CHUNK_SIZE || pos.y >= CHUNK_SIZE)
    return nullptr;

    return blockEntities.at(pos.x + pos.y * CHUNK_SIZE);
}

void Chunk::updateTileEntities(float delta)
{
    for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
    {
        if (blockEntities.at(i) != nullptr)
            blockEntities.at(i)->update(delta);
    }
}

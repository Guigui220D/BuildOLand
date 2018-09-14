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

Chunk::Chunk(World* world, std::queue<unsigned char>& data, sf::Vector2i chunkPos) : world(world)
{
    ready = false;
    //Check the size of the data
    if (data.size() < CHUNK_SIZE * CHUNK_SIZE * 2 + 1)
    {
        std::cout << "Could not load chunk " << chunkPos.x << ", " << chunkPos.y << " (invalid data size).\n";
        return;
    }
    //Get pos x and pos y
    {
        union
        {
            struct
            {
                int x;
                int y;
            } pos;
            unsigned char bytes[8];
        } upos;
        for (int i = 0; i < 8; i++)
        {
            upos.bytes[i] = data.front();
            data.pop();
        }
        position = sf::Vector2i(upos.pos.x, upos.pos.y);
    }
    if (chunkPos == position)   //Check the position
    {
        //Get grounds
        for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
        {
            unsigned char a = data.front();
            data.pop();
            grounds.push_back(a | data.front() << 8);
            data.pop();
        }
        //Then blocks
        unsigned char blockEntityCount = 0;
        std::vector<TileEntities*> tentities;
        for (int i = 0; i < (CHUNK_SIZE * CHUNK_SIZE); i++)
        {
            unsigned char a = data.front();
            data.pop();
            unsigned short block = (a | data.front() << 8);
            data.pop();
            blocks.push_back(block);
            TileEntityCodes codes = world->getStateGame()->getTileset()->getBlockById(block)->getTileEntity();
            blockEntityCount++;
            //Add block entity if needed
            switch (codes)
            {
            case TileEntityCodes::blinker:
                {
                    BlinkerTileE* e = new BlinkerTileE(world, sf::Vector2i(i % CHUNK_SIZE, i / CHUNK_SIZE));
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
            unsigned char fileBlockEntityCount = data.front();
            data.pop();
            if (fileBlockEntityCount != blockEntityCount || tentities.size() != fileBlockEntityCount)
            {
                std::cout << "Failed load chunk " << chunkPos.x << ", " << chunkPos.y << ", didn't load tile entities (count doesn't match).\n";
                return;
            }
            if (fileBlockEntityCount)
                std::cout << "Loading " << (int)fileBlockEntityCount << " tile entities\n";
            //Load data about each blockentity
            for (TileEntities* te : tentities)
            {
                union
                {
                    unsigned int i;
                    unsigned char bytes[4];
                } dataSize;
                for (int i = 0; i < 4; i++)
                {
                    dataSize.bytes[i] = data.front();
                    data.pop();
                }
                std::vector<unsigned char> teData;
                for (unsigned int i = 0; i < dataSize.i; i++)
                {
                    teData.front();
                    data.pop();
                }
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

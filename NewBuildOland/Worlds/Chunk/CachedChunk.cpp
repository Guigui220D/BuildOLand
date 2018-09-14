#include "CachedChunk.h"
#include "../../Entities/Entities.h"
#include "../../States/StateGame.h"

//Transform chunk to bytes
std::vector<unsigned char> CachedChunk::getData()
{
    std::vector<unsigned char> data;
    //Add position
    {
        union
        {
            int i;
            unsigned char bytes[4];
        } posX;
        posX.i = chunk->getPosition().x;
        for (int i = 0; i < 4; i++)
            data.push_back(posX.bytes[i]);
    }
    {
        union
        {
            int i;
            unsigned char bytes[4];
        } posY;
        posY.i = chunk->getPosition().y;
        for (int i = 0; i < 4; i++)
            data.push_back(posY.bytes[i]);
    }
    //Add grounds
    for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
    {
        for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
        {
            union
            {
                unsigned short i;
                unsigned char bytes[2];
            } ground;
            ground.i = chunk->getGround(sf::Vector2i(j, i));
            data.push_back(ground.bytes[0]);
            data.push_back(ground.bytes[1]);
        }
    }
    //Add blocks
    unsigned char blockEntityCount = 0;
    for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
    {
        for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
        {
            union
            {
                unsigned short i;
                unsigned char bytes[2];
            } block;
            block.i = chunk->getBlock(sf::Vector2i(j, i));
            if (chunk->getWorld()->getStateGame()->getTileset()->getBlockById(block.i)->getTileEntity() != TileEntityCodes::none)
                blockEntityCount++;
            data.push_back(block.bytes[0]);
            data.push_back(block.bytes[1]);
        }
    }
    //Add block entity count
    data.push_back(blockEntityCount);
    //Save block-entities data
    for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
    {
        for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
        {
            unsigned short block = chunk->getBlock(sf::Vector2i(i, j));
            if (chunk->getWorld()->getStateGame()->getTileset()->getBlockById(block)->getTileEntity() == TileEntityCodes::none)
                continue;
            if (chunk->getEntity(sf::Vector2i(i, j)) == nullptr)
            {
                std::cout << "An entity is missing on chunk " << chunk->getPosition().x << ", " << chunk->getPosition().y << ".\n";
                //Add 0 bytes of data
                for (int i = 0; i < 4; i++)
                    data.push_back((unsigned char)0);
                continue;
            }
            //Get the data and its size
            union
            {
                unsigned int i;
                unsigned char bytes[4];
            } dataSize;
            std::vector<unsigned char> ebData = chunk->getEntity(sf::Vector2i(i, j))->getData();
            dataSize.i = ebData.size();
            for (int i = 0; i < 4; i++)
                data.push_back(dataSize.bytes[i]);
            for (unsigned int i = 0; i < ebData.size(); i++)
                data.push_back(ebData.at(i));
        }
    }
    //Add entity count
    {
        union
        {
            int i;
            unsigned char bytes[4];
        } ecount;
        ecount.i = entities.size();
        for (int i = 0; i < 4; i++)
            data.push_back(ecount.bytes[i]);
    }
    //Add entities
    for (auto i = entities.begin(); i < entities.end(); i++)
    {
        std::vector<unsigned char> entityData = (*i)->getBytes();
        for (unsigned int j = 0; j < entityData.size(); j++)
            data.push_back(entityData.at(j));
    }
    return data;
}

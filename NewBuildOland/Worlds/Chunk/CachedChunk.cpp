#include "CachedChunk.h"
#include "../../Entities/Entities.h"

//Transform chunk to bytes
std::vector<unsigned char> CachedChunk::getData()
{
    std::vector<unsigned char> data;
    //Add position
    union
    {
        int i;
        unsigned char bytes[4];
    } posX;
    posX.i = chunk.getPosition().x;
    data.push_back(posX.bytes[0]);
    data.push_back(posX.bytes[1]);
    data.push_back(posX.bytes[2]);
    data.push_back(posX.bytes[3]);
    union
    {
        int i;
        unsigned char bytes[4];
    } posY;
    posY.i = chunk.getPosition().y;
    data.push_back(posY.bytes[0]);
    data.push_back(posY.bytes[1]);
    data.push_back(posY.bytes[2]);
    data.push_back(posY.bytes[3]);
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
            ground.i = chunk.getGround(sf::Vector2i(j, i));
            data.push_back(ground.bytes[0]);
            data.push_back(ground.bytes[1]);
        }
    }
    //Add blocks
    for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
    {
        for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
        {
            union
            {
                unsigned short i;
                unsigned char bytes[2];
            } block;
            block.i = chunk.getBlock(sf::Vector2i(j, i));
            data.push_back(block.bytes[0]);
            data.push_back(block.bytes[1]);
        }
    }
    //Add entity count
    data.push_back(((unsigned char)(entities.size()) & 0x000000FF) >> 0);
    data.push_back(((unsigned char)(entities.size()) & 0x0000FF00) >> 8);
    data.push_back(((unsigned char)(entities.size()) & 0x00FF0000) >> 16);
    data.push_back(((unsigned char)(entities.size()) & 0xFF000000) >> 24);
    //Add entities
    for (auto i = entities.begin(); i < entities.end(); i++)
    {
        std::vector<unsigned char> entityData = (*i)->getBytes();
        for (int j = 0; j < entityData.size(); j++)
            data.push_back(entityData.at(j));
    }
    return data;
}

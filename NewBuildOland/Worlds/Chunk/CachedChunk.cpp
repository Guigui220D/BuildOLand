#include "CachedChunk.h"
#include "../../Entities/Entities.h"

//Transform chunk to bytes
std::vector<unsigned char> CachedChunk::getData()
{
    std::vector<unsigned char> data;
    //Add position
    data.push_back((chunk.getPosition().x & 0x000000FF) << 0);
    data.push_back((chunk.getPosition().x & 0x0000FF00) << 8);
    data.push_back((chunk.getPosition().x & 0x00FF0000) << 16);
    data.push_back((chunk.getPosition().x & 0xFF000000) << 24);
    data.push_back((chunk.getPosition().y & 0x000000FF) << 0);
    data.push_back((chunk.getPosition().y & 0x0000FF00) << 8);
    data.push_back((chunk.getPosition().y & 0x00FF0000) << 16);
    data.push_back((chunk.getPosition().y & 0xFF000000) << 24);
    //Add grounds
    for (int i = 0; i < (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE); i++)
    {
        for (int j = 0; j < (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE); j++)
        {
            data.push_back(chunk.getGround(sf::Vector2i(i, j)) & 0x00FF);
            data.push_back((chunk.getGround(sf::Vector2i(i, j)) & 0xFF00) >> 8);
        }
    }
    //Add blocks
    for (int i = 0; i < (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE); i++)
    {
        for (int j = 0; j < (Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE); j++)
        {
            data.push_back(chunk.getBlock(sf::Vector2i(i, j)) & 0x00FF);
            data.push_back((chunk.getBlock(sf::Vector2i(i, j)) & 0xFF00) >> 8);
        }
    }
    //Add entity count
    data.push_back(((int)(entities.size()) & 0x000000FF) << 0);
    data.push_back(((int)(entities.size()) & 0x0000FF00) << 8);
    data.push_back(((int)(entities.size()) & 0x00FF0000) << 16);
    data.push_back(((int)(entities.size()) & 0xFF000000) << 24);
    //Add entities
    for (auto i = entities.begin(); i < entities.end(); i++)
    {
        std::vector<unsigned char> entityData = (*i)->getBytes();
        for (int j = 0; j < entityData.size(); j++)
            data.push_back(entityData.at(j));
    }
    return data;
}

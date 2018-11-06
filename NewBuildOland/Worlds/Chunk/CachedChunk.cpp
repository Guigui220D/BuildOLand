#include "CachedChunk.h"
#include "../../Entities/Entities.h"
#include "../../States/StateGame.h"
#include "../../Utils/VarToBytes.h"

//Transform chunk to bytes
std::vector<unsigned char> CachedChunk::getData()
{
    std::vector<unsigned char> data;
    //Add position
    {
        VarU<int> posx(chunk->getPosition().x);
        VarU<int> posy(chunk->getPosition().y);
        for (auto i = 0u; i < posx.size(); i++)
            data.push_back(posx[i]);
        for (auto i = 0u; i < posy.size(); i++)
            data.push_back(posy[i]);
    }
    //Add grounds
    for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
        for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
        {
            VarU<unsigned short> ground(chunk->getGround(sf::Vector2i(j, i)));
            data.push_back(ground[0]);
            data.push_back(ground[1]);
        }
    //Add blocks
    unsigned char blockEntityCount = 0;
    for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
        for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
        {
            VarU<unsigned short> block(chunk->getBlock(sf::Vector2i(j, i)));
            data.push_back(block[0]);
            data.push_back(block[1]);

            if (chunk->getWorld()->getStateGame()->getTileset()->getBlockById(block())->getTileEntity() != TileEntityCodes::none)
                blockEntityCount++;
        }
    //Add block entity count
    data.push_back(blockEntityCount);
    //Save block-entities data
    for (int i = 0; i < Chunk::CHUNK_SIZE; i++)
        for (int j = 0; j < Chunk::CHUNK_SIZE; j++)
        {
            unsigned short block = chunk->getBlock(sf::Vector2i(i, j));
            if (chunk->getWorld()->getStateGame()->getTileset()->getBlockById(block)->getTileEntity() == TileEntityCodes::none)
                continue;
            if (chunk->getEntity(sf::Vector2i(i, j)) == nullptr)
            {
                std::cout << "An entity is missing on chunk " << chunk->getPosition().x << ", " << chunk->getPosition().y << ".\n";
                //Add 0 bytes of empty data (the size is null)
                for (auto i = 0u; i < sizeof(int); i++)
                    data.push_back((unsigned char)0);
                continue;
            }
            //Get the data and its size
            std::vector<unsigned char> ebData = chunk->getEntity(sf::Vector2i(i, j))->getData();
            VarU<unsigned int> dataSize(ebData.size());
            //Add the data size
            for (auto i = 0u; i < dataSize.size(); i++)
                data.push_back(dataSize[i]);
            //Add the data
            for (unsigned int i = 0; i < ebData.size(); i++)
                data.push_back(ebData.at(i));
        }
    //Add the entity count
    {
        VarU<int> ecount(entities.size());
        for (auto i = 0u; i < ecount.size(); i++)
            data.push_back(ecount[i]);
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

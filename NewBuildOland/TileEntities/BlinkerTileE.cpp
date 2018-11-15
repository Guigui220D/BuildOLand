#include "BlinkerTileE.h"
#include "../Worlds/World.h"

BlinkerTileE::BlinkerTileE(World* world, sf::Vector2i blockPos) : TileEntities(world, blockPos)
{
    //ctor
}

BlinkerTileE::~BlinkerTileE()
{
    //dtor
}

void BlinkerTileE::update(float delta)
{
    getWorld()->setBlockId(getPosition() + sf::Vector2i(1, 0), block);
    block = !block;
}

void BlinkerTileE::draw(sf::RenderWindow& window) {}

void BlinkerTileE::takeData(std::vector<unsigned char> data)
{}

std::vector<unsigned char> BlinkerTileE::getData()
{
    return std::vector<unsigned char>();
}

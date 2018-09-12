#include "TileEntities.h"
#include "../Worlds/World.h"
#include <iostream>

TileEntities::TileEntities(World* world, sf::Vector2i blockPos) :
    world(world),
    pos(blockPos)
{

}

TileEntities::~TileEntities()
{

}

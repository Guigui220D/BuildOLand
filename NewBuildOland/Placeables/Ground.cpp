#include "Ground.h"

Ground::Ground(sf::IntRect textureRect, std::string name, sf::Color mapColor) : Placeable(textureRect, name, mapColor)
{
}

Ground::~Ground()
{
}

bool Ground::isGround() {
    return true;
}

#pragma once
#include "../Utils/TileSet.h"

class TestTileSet : public TileSet
{
public:
	sf::IntRect getGroundRect(unsigned int id) override;
    sf::IntRect getBlockRect(unsigned int id) override;
};


#pragma once
#include "../Utils/TileSet.h"

class TestTileSet : public TileSet
{
public:
	TestTileSet();
	~TestTileSet();
	sf::IntRect getGroundRect(unsigned int id) override;
    sf::IntRect getBlockRect(unsigned int id) override;
};


#pragma once
#include "Block.h"

class BlockTeleporter : public Block
{
public:
	BlockTeleporter(sf::IntRect textureRect);
	~BlockTeleporter();

	//Event methods
	void onPlaceableEnter(PlaceableEnterEvent e) override;
};


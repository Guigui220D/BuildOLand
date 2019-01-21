#pragma once
#include "../Block.h"

class BlockSaver : public Block
{
public:
	BlockSaver(sf::IntRect textureRect);
	~BlockSaver();

	//Event methods
	void onPlaceableEnter(PlaceableEnterEvent e) override;
};


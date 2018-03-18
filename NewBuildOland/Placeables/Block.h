#pragma once
#include "Placeable.h"

class Block : public Placeable
{
public:
	Block(sf::IntRect textureRect = sf::IntRect(), std::string name = "", sf::Color mapColor = sf::Color(255, 255, 255));
	~Block();
};


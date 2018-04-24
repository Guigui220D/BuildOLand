#pragma once
#include "Placeable.h"

class Ground : public Placeable
{
public:
	Ground(sf::IntRect textureRect = sf::IntRect(), std::string name = "", sf::Color mapColor = sf::Color(255, 255, 255));
	~Ground();

	//Item methods
	bool isGround() override;
};


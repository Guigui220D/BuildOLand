#pragma once
#include "Placeable.h"

class Ground : public Placeable
{
public:
	Ground(sf::IntRect textureRect = sf::IntRect(), std::string name = "", sf::Color mapColor = sf::Color(255, 255, 255));
	~Ground();

	//Event methods
	void OnPlaceableEnter(PlaceableEnterEvent e) override;

	void OnPlaceableLeave(PlaceableLeaveEvent e) override;

	//Item methods
	bool isGround() override;
};


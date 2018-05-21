#pragma once
#include "Placeable.h"

class StateGame;

class Ground : public Placeable
{
public:
	Ground(sf::IntRect textureRect = sf::IntRect(), std::string name = "", sf::Color mapColor = sf::Color(255, 255, 255));

    virtual ~Ground();

	virtual Ground* getGroundOnBreak(StateGame *stateGame);

	//Event methods
	void onPlaceableEnter(PlaceableEnterEvent e) override;

	void onPlaceableLeave(PlaceableLeaveEvent e) override;

	//Item methods
	bool isGround() override;
};


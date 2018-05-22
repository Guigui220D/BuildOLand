#pragma once
#include "Placeable.h"

class BlockBuildEvent;
class BlockBreakEvent;
class PlaceableEnterEvent;
class PlaceableLeaveEvent;
class BlockInteractEvent;
class StateGame;

class Block : public Placeable
{
public:
	Block(sf::IntRect textureRect, std::string name = "", sf::Color mapColor = sf::Color(255, 255, 255), bool hasHitbox = true, bool hasVolume = true, sf::IntRect side = sf::IntRect());
	~Block();
	bool hasHitbox();
	bool hasVolume();
	sf::IntRect getSideRect();
	sf::Color getSideTint();

	virtual Block* getBlockOnBreak(StateGame* stateGame);

	//Event methods
	virtual void onBlockBuild(BlockBuildEvent e);
	virtual void onBlockBreak(BlockBreakEvent e);
	virtual void onBlockInteract(BlockInteractEvent e);

	//Item methods
	bool isGround() override;

private:
	bool mHasHitbox;
	bool mHasVolume;
	sf::IntRect sideRect;
};


#pragma once
#include "Placeable.h"
#include "../Entities/EntityCodes.h"

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
	inline bool hasHitbox() { return mHasHitbox; };
	inline bool hasVolume() { return mHasVolume; };
	inline sf::IntRect getSideRect() { return sideRect; };
	inline sf::Color getSideTint()
	{
        if (sideRect == sf::IntRect())
            return sf::Color(127, 127, 127);
        return sf::Color::White;
	};

	virtual Block* getBlockOnBreak(StateGame* stateGame);

	virtual inline TileEntityCodes getTileEntity() { return TileEntityCodes::none; }

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


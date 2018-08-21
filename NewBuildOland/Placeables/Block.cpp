#include "Block.h"
#include "../Events/EventManager.h"

Block::Block(sf::IntRect textureRect, std::string name, sf::Color mapColor, bool hasHitbox, bool hasVolume, sf::IntRect side) : Placeable(textureRect, name, mapColor)
, mHasHitbox(hasHitbox), mHasVolume(hasVolume), sideRect(side)
{
}

Block::~Block()
{
}

//Event methods
void Block::onBlockBuild(BlockBuildEvent e)
{
	Sound* blockPlaceSound = e.getState()->getSoundManager()->getSound("blockPlace.ogg");
	blockPlaceSound->setVolume(30);
	blockPlaceSound->play();

}
void Block::onBlockBreak(BlockBreakEvent e)
{

}
void Block::onBlockInteract(BlockInteractEvent e)
{

}

bool Block::isGround()
{
    return false;
}

Block *Block::getBlockOnBreak(StateGame* stateGame)
{
	return this;
}

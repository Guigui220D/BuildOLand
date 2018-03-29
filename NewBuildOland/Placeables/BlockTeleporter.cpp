#include "stdafx.h"
#include "BlockTeleporter.h"
#include "../Events/Events.h"
#include "../Worlds/FlatWorld.h"

BlockTeleporter::BlockTeleporter(sf::IntRect textureRect) : Block(textureRect, "TELEPORTER", sf::Color(150, 50, 50), false, false)
{
}


BlockTeleporter::~BlockTeleporter()
{
}


void BlockTeleporter::OnBlockBuild(BlockBuildEvent e) {

}

void BlockTeleporter::OnBlockBreak(BlockBreakEvent e) {
	//Change the world
	FlatWorld* fw = new FlatWorld(*e.getState());
	e.getState()->setWorld(*fw);
}

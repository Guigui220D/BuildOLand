#include "BlockTeleporter.h"
#include "../Events/EventManager.h"


BlockTeleporter::BlockTeleporter(sf::IntRect textureRect) : Block(textureRect, "TELEPORTER", sf::Color(150, 50, 50), false, false)
{
}


BlockTeleporter::~BlockTeleporter()
{
}

void BlockTeleporter::onPlaceableEnter(PlaceableEnterEvent e)
{
	//Play a teleportation sound
	sf::Sound teleportSound;
	teleportSound.setBuffer(*e.getState()->getAssetManager()->getSound("TELEPORT"));
	teleportSound.setVolume(20);
	teleportSound.play();
}


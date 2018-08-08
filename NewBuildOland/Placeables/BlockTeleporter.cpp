#include "BlockTeleporter.h"
#include "../Events/EventManager.h"
#include "../Worlds/FlatWorld.h"
#include "../Worlds/MazeWorld.h"

BlockTeleporter::BlockTeleporter(sf::IntRect textureRect) : Block(textureRect, "TELEPORTER", sf::Color(150, 50, 50), false, false)
{
}


BlockTeleporter::~BlockTeleporter()
{
}

void BlockTeleporter::onPlaceableEnter(PlaceableEnterEvent e) {

    World* oldWorld = e.getState()->getWorld();
    World* newWorld = nullptr;

    //Set the world according to the world the stateGame is in
    if(oldWorld->getName() == "flatworld") {
        newWorld = new MazeWorld(*e.getState());
    } else {
        newWorld = new FlatWorld(*e.getState());
    }

    //Send it to the stateGame to change the world
    e.getState()->setWorld(*newWorld);

	//Play a teleportation sound
	sf::Sound* teleportSound = e.getState()->getSoundManager()->getSound("teleport.ogg");
	teleportSound->setVolume(20);
	teleportSound->play();
}


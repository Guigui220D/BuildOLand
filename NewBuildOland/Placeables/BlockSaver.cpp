#include "BlockSaver.h"
#include "../Events/EventManager.h"
#include "../Worlds/FlatWorld.h"

BlockSaver::BlockSaver(sf::IntRect textureRect) : Block(textureRect, "PROTO_SAVER", sf::Color(255, 0, 0), false, false)
{
}


BlockSaver::~BlockSaver()
{

}


void BlockSaver::onPlaceableEnter(PlaceableEnterEvent e) {
	std::cout << "Saved the world!" << std::endl;
	e.getState()->getWorld()->saveWorld();

	//Play a sound
	sf::Sound* saveSound = e.getState()->getSoundManager()->getSound("save.ogg");
	saveSound->setVolume(20);
	saveSound->play();
}

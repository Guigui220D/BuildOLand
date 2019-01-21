#include "BlockSaver.h"
#include "../Events/EventManager.h"

BlockSaver::BlockSaver(sf::IntRect textureRect) : Block(textureRect, "PROTO_SAVER", sf::Color(255, 0, 0), false, false)
{
}


BlockSaver::~BlockSaver()
{

}


void BlockSaver::onPlaceableEnter(PlaceableEnterEvent e) {
	std::cout << "Saved the world!" << std::endl;
	e.getState()->getWorld()->flushChunkCache();

	//Play a sound
	sf::Sound* saveSound = new sf::Sound();
	e.getState()->getAssetManager()->addPlayingSound(saveSound);
	saveSound->setBuffer(*e.getState()->getAssetManager()->getSound("SAVE"));
	saveSound->setVolume(20);
	saveSound->play();
}

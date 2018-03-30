#include "stdafx.h"
#include "BlockSaver.h"
#include "../Events/EventManager.h"
#include "../Worlds/FlatWorld.h"

BlockSaver::BlockSaver(sf::IntRect textureRect) : Block(textureRect, "PROTO_SAVER", sf::Color(255, 0, 0), false, false)
{
}


BlockSaver::~BlockSaver()
{

}


void BlockSaver::OnPlaceableEnter(PlaceableEnterEvent e) {
	std::cout << "Saved the world!" << std::endl;
	e.getState()->getWorld()->saveWorld();
}
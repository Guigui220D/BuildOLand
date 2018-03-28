#include "stdafx.h"
#include "World.h"
#include "../Utils/FileManager.h"
#include "../Game.h"
#include "../States/StateBase.h"

#include <fstream>
#include <iostream>
#include <Windows.h>

World::World(StateGame& stateGame, std::string name)
	: stateGame(&stateGame)
{
	worldName = name;
}

//Loads the world file and saves it in an array
//Returns true if sucess
bool World::loadWorld()
{
	//Check if file exists
	std::string const worldFileName("./../gamedata/worlds/" + worldName + ".bol");
	
	std::ifstream worldFile(worldFileName.c_str(), std::ios::binary | std::ios::in);
	if(worldFile.is_open()) {
		//The file exists, we can read it now

		//Get the worldSize from file
		unsigned int worldSizeX;
		unsigned int worldSizeY;
		worldFile.read((char*)(&worldSizeX), sizeof(worldSize.x));
		worldFile.read((char*)(&worldSizeY), sizeof(worldSize.y));
		worldSize = sf::Vector2u(worldSizeX, worldSizeY);
		
		unsigned short idBuffer;
		//Read the groundId array from the file
		for (unsigned int i = 0; i < worldSize.x * worldSize.y; i++) {
			worldFile.read((char*)(&idBuffer), sizeof(idBuffer));
			groundIds.push_back(idBuffer);
		}
		//Read the blockId array from the file
		for (unsigned int i = 0; i < worldSize.x * worldSize.y; i++) {
			worldFile.read((char*)(&idBuffer), sizeof(idBuffer));
			blockIds.push_back(idBuffer);
		}
		
		//We can close the file, all the data has been loaded
		worldFile.close();
		return true;
	} else {
		//The file doesn't exist, create one
		
		//Create the folder (for windows only)
		std::string const worldFolderName("./../gamedata/worlds/");
		FileManager::createFolder(worldFolderName);

		//Create the file
		std::ofstream worldFileFlux(worldFileName.c_str(), std::ios::binary | std::ios::out);
		if(worldFileFlux) {
			//Everything okay, ready to write

			//Call the child classes to generate a world
			this->generateWorld();

			saveWorldToFile(worldFileFlux);

			worldFileFlux.close();
			return true;
		} else {
			return false;
		}
	}

	return true;
}

bool World::saveWorld()
{
	std::string const worldFileName("./../gamedata/worlds/" + worldName + ".bol");

	//Recreate the file
	std::ofstream worldFileFlux(worldFileName.c_str(), std::ios::binary | std::ios::out);
	if (worldFileFlux) {
		//Everything okay, ready to write

		saveWorldToFile(worldFileFlux);

		worldFileFlux.close();
		return true;
	}
	else {
		return false;
	}
}

void World::saveWorldToFile(std::ofstream &worldFileFlux) {
	
	//First save the size of the world
	worldFileFlux.write((char*)(&worldSize.x), sizeof(worldSize.x));
	worldFileFlux.write((char*)(&worldSize.y), sizeof(worldSize.y));

	//Save the groundIds array that were generated
	for (unsigned int i = 0; i < groundIds.size(); i++) {
		worldFileFlux.write((char*)(&groundIds[i]), sizeof(unsigned short));
	}
	//And save the blockIds array
	for (unsigned int i = 0; i < blockIds.size(); i++) {
		worldFileFlux.write((char*)(&blockIds[i]), sizeof(unsigned short));
	}
}

unsigned short World::getGroundId(unsigned short x, unsigned short y)
{
	//If pos is out of map
	if (x < 0 || x >= worldSize.x ||
		y < 0 || y >= worldSize.y) {
		return 0;
	}
	return groundIds[y + x * worldSize.x];
}

unsigned short World::getGroundId(sf::Vector2u pos)
{
	return getGroundId(pos.x, pos.y);
}

unsigned short World::getBlockId(unsigned short x, unsigned short y)
{
	//If pos is out of map
	if (x < 0 || x >= worldSize.x ||
		y < 0 || y >= worldSize.y) {
		return 0;
	}
	return blockIds[y + x * worldSize.x];
}

unsigned short World::getBlockId(sf::Vector2u pos)
{
	return getBlockId(pos.x, pos.y);
}

Block* World::getBlockAt(sf::Vector2u pos) {
	getBlockAt(pos.x, pos.y);
}

Block* World::getBlockAt(unsigned short x, unsigned short y) {
	unsigned short blockId = getBlockId(x, y);
	return stateGame->getTileset()->getBlockById(blockId);
}

void World::setGroundId(unsigned short x, unsigned short y, unsigned short value)
{
	//If pos is out of map
	if (x < 0 || x >= worldSize.x ||
		y < 0 || y >= worldSize.y) {
		return;
	}

	groundIds[y + x * worldSize.x] = value;
}


void World::setGroundId(sf::Vector2u pos, unsigned short value)
{
	setGroundId(pos.x, pos.y, value);
}

void World::setBlockId(unsigned short x, unsigned short y, unsigned short value)
{
	//If pos is out of map
	if (x < 0 || x >= worldSize.x ||
		y < 0 || y >= worldSize.y) {
		return;
	}

	blockIds[y + x * worldSize.x] = value;
}

void World::setBlockId(sf::Vector2u pos, unsigned short value)
{
	setBlockId(pos.x, pos.y, value);
}

sf::Vector2u World::getWorldSize()
{
	return worldSize;
}

sf::Vector2u World::getInitialPlayerPos()
{
	return playerPos;
}

World::~World()
{
}


#include "stdafx.h"
#include "World.h"
#include "../Utils/FileManager.h"

#include <fstream>
#include <iostream>
#include <Windows.h>

World::World(Game& game)
	: game(&game)
{
}

//Loads the world file and saves it in an array
//Returns true if sucess
bool World::loadWorld()
{
	//Check if file exists
	std::string const worldFileName("./../gamedata/worlds/" + worldName + ".bol");
	
	std::ifstream worldFile(worldFileName.c_str());
	if(worldFile) {
		//The file exists, we can read it now

		//Get the content of the file and save it as an array

		return true;
	} else {
		//The file doesn't exist, create one
		
		//Create the folder (for windows only)
		std::string const worldFolderName("./../gamedata/worlds/");
		FileManager::createFolder(worldFolderName);

		//Create the file
		std::ofstream testFlux(worldFileName.c_str());
		if(testFlux) {
			//Everything okay, ready to write

			//Call the child classes to generate a world
			this->generateWorld();
			
			//Todo : save the array generateWorld() has returned in the file and as a variable

			return true;
		} else {
			return false;
		}
	}

	return true;
}

unsigned short World::getGroundId(sf::Vector2u pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= worldSize.x || pos.y >= worldSize.y)
		return 0;
	return 1;
}

unsigned short World::getBlockId(sf::Vector2u pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= worldSize.x || pos.y >= worldSize.y)
		return 0;
	return 0;
}

void World::setGroundId(sf::Vector2u pos, unsigned short value)
{
}

void World::setBlockId(sf::Vector2u pos, unsigned short value)
{
}

sf::Vector2u World::getSize()
{
	return worldSize;
}

World::~World()
{
}


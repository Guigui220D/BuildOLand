#pragma once
#include <SFML\system.hpp>
#include <vector>
#include "../Utils/TileSet.h"
#include "../Placeables/Block.h"

class Game;

class World
{
public:
	World(Game& game, std::string name = "world1");
	
	//Loads the world with the WorldManager class ?
	//And returns true if success
	bool loadWorld();
	bool saveWorld();
	
	//Method that generates the world procedurally
	virtual void generateWorld() = 0;

	unsigned short getGroundId(unsigned short x, unsigned short y);
	unsigned short getGroundId(sf::Vector2u pos);
	unsigned short getBlockId(unsigned short x, unsigned short y);
	unsigned short getBlockId(sf::Vector2u pos);
	Block* getBlockAt(sf::Vector2u pos);
	Block* getBlockAt(unsigned short x, unsigned short y);
	void setGroundId(unsigned short x, unsigned short y, unsigned short value);
	void setGroundId(sf::Vector2u pos, unsigned short value);
	void setBlockId(unsigned short x, unsigned short y, unsigned short value);
	void setBlockId(sf::Vector2u pos, unsigned short value);
	
	sf::Vector2u getWorldSize();
	sf::Vector2u getInitialPlayerPos();

	~World();

protected:
	Game* game = nullptr;

	long worldSeed;
	std::string worldName;
	sf::Vector2u worldSize;

	sf::Vector2u playerPos;

	std::vector<unsigned short> groundIds;
	std::vector<unsigned short> blockIds;

private:
	void saveWorldToFile(std::ofstream &worldFileFlux);
	
};


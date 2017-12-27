#pragma once
#include <SFML\system.hpp>

class Game;

class World
{
public:
	World(Game& game);
	
	//Loads the world with the WorldManager class ?
	//And returns true if success
	bool loadWorld();
	
	//Method that generates the world procedurally
	virtual void generateWorld() = 0;

	virtual unsigned short getGroundId(sf::Vector2u pos);
	virtual unsigned short getBlockId(sf::Vector2u pos);
	virtual void setGroundId(sf::Vector2u pos, unsigned short value);
	virtual void setBlockId(sf::Vector2u pos, unsigned short value);

	~World();

protected:
	Game* game = nullptr;

	std::string worldName = "world1";
	sf::Vector2u worldSize;
	long worldSeed;

};


#pragma once
#include <SFML\system.hpp>
#include <vector>
#include "../Utils/TileSet.h"
#include "../Placeables/Block.h"


class Entities;

class StateGame;

class World
{
public:
	World(StateGame& stateGame, std::string name = "world1");

	//Loads the world with the WorldManager class ?
	//And returns true if success
	virtual bool loadWorld();
	virtual bool saveWorld();

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
	std::string getName();
	StateGame* getStateGame();

	const std::vector<Entities*> &getEntities() const;
    virtual void addEntity(Entities* entity);
	virtual void removeEntitiesThatNeedToBeRemoved();
	inline unsigned int getNextEntityId()
    {
        nextEntityId++;
        return nextEntityId - 1;
    }

	//Call for telling the other methods that the world is deleted
	void setDeleted();
	~World();
protected:
	StateGame* stateGame = nullptr;

	long worldSeed;
	std::string worldName;
	sf::Vector2u worldSize;

	sf::Vector2u playerPos;

	std::vector<unsigned short> groundIds;
	std::vector<unsigned short> blockIds;

	std::vector<Entities*> entities;

private:
	void saveWorldToFile(std::ofstream &worldFileFlux);
	bool isBeingDeleted = false;

	unsigned int nextEntityId = 0;

};


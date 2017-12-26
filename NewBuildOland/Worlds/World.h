#pragma once
#include <SFML\system.hpp>

class World
{
public:
	World();
	~World();
	virtual unsigned short getGround(sf::Vector2u pos);
	virtual unsigned short getBlock(sf::Vector2u pos);
	virtual void setGround(sf::Vector2u pos, unsigned short value);
	virtual void setBlock(sf::Vector2u pos, unsigned short value);
	sf::Vector2u size;

};


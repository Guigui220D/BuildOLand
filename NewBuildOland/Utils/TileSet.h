#pragma once
#include <SFML\graphics.hpp>

//This is the tileset class that allows to get textures from a block id
//All the tilsets should be in Res/

class TileSet
{
public:
	TileSet(sf::Texture text);
	~TileSet();
	virtual sf::IntRect getGroundRect(unsigned int id);
	virtual sf::IntRect getBlockRect(unsigned int id);
protected:
	sf::Texture texture;
};


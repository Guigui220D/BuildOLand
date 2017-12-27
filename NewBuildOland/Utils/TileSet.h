#pragma once
#include <SFML\graphics.hpp>

//This is the tileset class that allows to get textures from a block id
//All the tilsets should be in Res/

class TileSet
{
public:
	TileSet();
	~TileSet();
	sf::IntRect getGroundRect(unsigned int id);
	sf::IntRect getBlockRect(unsigned int id);
	sf::Texture* getTexture();
protected:
	sf::Texture texture;
};


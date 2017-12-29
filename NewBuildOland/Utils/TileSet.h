#pragma once
#include <SFML\graphics.hpp>

//This is the tileset class that allows to get textures from a block id
//All the tilsets should be in Res/

using namespace sf;

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
	sf::IntRect groundRects[3] = 
	{
		IntRect(0, 8, 8, 8),
		IntRect(8, 0, 8, 8),
		IntRect(8, 8, 8, 8)
	};
	sf::IntRect blockRects[1] = 
	{
		IntRect()
	};
	sf::IntRect errorRect = IntRect(0, 0, 8, 8);
	const unsigned int groundRectsSize = 3;
	const unsigned int blockRectsSize = 1;
};
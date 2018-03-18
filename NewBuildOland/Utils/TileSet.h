#pragma once
#include <SFML\graphics.hpp>
#include "../Placeables/Ground.h"
#include "../Placeables/Block.h"
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
	sf::Color getMapPixel(unsigned int groundId, unsigned int blockId);
	sf::Texture* getTexture();

protected:
	const unsigned int TILES_IN_ROW = 2;
	const unsigned int TILE_SIZE = 8;
	sf::Texture texture;
	
	sf::IntRect errorRect = IntRect(0, 0, 8, 8);
	sf::Color errorColor = Color(255, 0, 255);

private:
	void generateBlocks();
	void generateGrounds();
	
	sf::IntRect rectById(unsigned int tilesetId);

	std::vector<Block*> blocks;
	std::vector<Ground*> grounds;

};
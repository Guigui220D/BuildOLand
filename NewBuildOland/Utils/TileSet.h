#pragma once
#include <SFML\graphics.hpp>
#include "../Placeables/Ground.h"
#include "../Placeables/Block.h"
#include <unordered_map>
#include <math.h>
//This is the tileset class that allows to get textures from a block id
//All the tilsets should be in Res/

class TileSet
{
public:
	TileSet();
	~TileSet();

	//Get the rectangles to draw the map (in the TILESET texture) using rectById()
	inline sf::IntRect getBlockRect(unsigned int id) const
        { return (id < blocks.size()) ? (blocks.at(id)->getTextureRect()) : (errorRect); }
    inline sf::IntRect getGroundRect(unsigned int id) const
        { return (id < grounds.size()) ? (grounds.at(id)->getTextureRect()) : (errorRect); }
	sf::IntRect getBlockSideRect(unsigned int id) const;

	sf::Color getMapPixel(unsigned int groundId, unsigned int blockId) const;
	inline sf::Color getSideTint(unsigned int id) const
        { return (id < blocks.size()) ? (blocks[id]->getSideTint()) : (sf::Color::White); }

	//Get a tile object using its ID
	inline Block* getBlockById(unsigned int id) const
        { return blocks.at(id); }
    inline Ground* getGroundById(unsigned int id) const
        { return grounds.at(id); }

    //Get an id using a name
	unsigned short getBlockIdByName(const std::string name) const;
	unsigned short getGroundIdByName(const std::string name) const;

	//Get a tile using its name
	inline Block* getBlockByName(std::string name) const
        { return blocks.at(getBlockIdByName(name)); }
	inline Ground* getGroundByName(std::string name) const
        { return grounds.at(getGroundIdByName(name)); }

	inline unsigned int getBlockCount() const { return blocks.size(); }
	inline unsigned int getGroundCount() const { return grounds.size(); }

	inline sf::Texture* getTexture() const { return tileset; }

private:
	const unsigned int TILES_IN_ROW = 5;
	const unsigned int TILE_SIZE = 32;

	sf::Texture* tileset;

	sf::IntRect errorRect = sf::IntRect(0, 0, 8, 8);
	sf::Color errorColor = sf::Color(255, 0, 255);

	//Creates an IntRect where the texture is according to the nth texture of the tileset
    inline sf::IntRect rectById(unsigned int tilesetId) const
        { return sf::IntRect(tilesetId % TILES_IN_ROW * (TILE_SIZE + 2) + 1, (int)floorf(tilesetId / TILES_IN_ROW) * (TILE_SIZE + 2) + 1, TILE_SIZE, TILE_SIZE); }

	//Adds a tile
    void addTile(Placeable* tile);

    //Add all grounds and block (do once on constructor)
	void generateBlocks();
	void generateGrounds();

	std::vector<Block*> blocks;
	std::vector<Ground*> grounds;
	std::unordered_map<std::string, unsigned short> blockNames;
	std::unordered_map<std::string, unsigned short> groundNames;
};

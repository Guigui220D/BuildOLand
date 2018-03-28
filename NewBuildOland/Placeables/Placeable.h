#pragma once
#include <SFML\Graphics.hpp>

class Placeable
{
public:
	Placeable(sf::IntRect textureRect = sf::IntRect(), std::string name = "", sf::Color mapColor = sf::Color(255, 255, 255));
	~Placeable();
	sf::Color getColor();
	sf::IntRect getTextureRect();
	std::string getName();


protected:
	//Used to get the right texture from the tileset
	sf::IntRect textureRect;
	sf::Color mapColor;
	std::string name;
};


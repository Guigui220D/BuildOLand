#pragma once
#include <SFML\Graphics.hpp>

class PlaceableEnterEvent;
class PlaceableLeaveEvent;


class Placeable
{
public:
	Placeable(sf::IntRect textureRect = sf::IntRect(), std::string name = "", sf::Color mapColor = sf::Color(255, 255, 255));
	~Placeable();
	sf::Color getColor();
	sf::IntRect getTextureRect();
	std::string getName();

	virtual void OnPlaceableEnter(PlaceableEnterEvent e);
	virtual void OnPlaceableLeave(PlaceableLeaveEvent e);

protected:
	//Used to get the right texture from the tileset
	sf::IntRect textureRect;
	sf::Color mapColor;
	std::string name;
};


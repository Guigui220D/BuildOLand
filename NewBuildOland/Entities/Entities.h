#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"

class Entities : public sf::RectangleShape
{
public:
	Entities();
	~Entities();
	virtual void update(double delta);
	sf::CircleShape* getOnMap();
	void setOnMapColor(sf::Color color);
	void setOnMapRadius(float radius);
private:
	sf::CircleShape onMap;
};

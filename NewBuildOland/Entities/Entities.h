#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "../Worlds/World.h"

class Entities : public sf::RectangleShape
{
public:
	Entities(World *world);
	~Entities();
	virtual void update(double delta);
	sf::CircleShape* getOnMap();
	void setOnMapColor(sf::Color color);
	void setOnMapRadius(float radius);
	void setCurrentWorld(World *world);

	sf::Vector2f getWorldPos();
protected:
	World *currentWorld = nullptr;

private:
	sf::CircleShape onMap;
	
};


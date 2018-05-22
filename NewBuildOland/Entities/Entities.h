#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "../Worlds/World.h"

class Entities : public sf::RectangleShape
{
public:
	Entities(World *world, unsigned int id);
	~Entities();
	virtual void update(double delta);

	sf::CircleShape* getOnMap();
	inline void setOnMapColor(sf::Color color) { onMap.setFillColor(color); };
	void setOnMapRadius(float radius) { onMap.setRadius(radius); };

	sf::Vector2f getWorldPos();

	inline World *getCurrentWorld() const { return currentWorld; };

	bool mustBeRemoved = false;

	inline unsigned int getID() { return id; };

protected:
	World *currentWorld = nullptr;

private:
	sf::CircleShape onMap;

	unsigned int id;

};


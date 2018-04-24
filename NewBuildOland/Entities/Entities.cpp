#include "Entities.h"


Entities::Entities(World *world)
	: currentWorld(world)
{
	onMap.setFillColor(sf::Color::Yellow);
	onMap.setRadius(50);
	onMap.setOrigin(sf::Vector2f(50, 50));
}


Entities::~Entities()
{
}

void Entities::update(double delta)
{
}

sf::CircleShape* Entities::getOnMap()
{
	onMap.setPosition(getPosition());
	return &onMap;
}

void Entities::setOnMapColor(sf::Color color)
{
	onMap.setFillColor(color);
}

void Entities::setOnMapRadius(float radius)
{
	onMap.setRadius(radius);
}

void Entities::setCurrentWorld(World *world)
{
	currentWorld = world;
}

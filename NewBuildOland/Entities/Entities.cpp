#include "Entities.h"
#include "../States/StateGame.h"


Entities::Entities(World *world)
	: currentWorld(world)
{
	onMap.setFillColor(sf::Color::Yellow);
	onMap.setRadius(50);
	onMap.setOrigin(sf::Vector2f(50, 50));

	id = world->getStateGame()->getEntityId();
	std::cout << "Entity got id " << id << std::endl;
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

sf::Vector2f Entities::getWorldPos() {
	sf::Vector2f position = getPosition();

	return sf::Vector2f(position.x / StateGame::TILE_SIZE, position.y / StateGame::TILE_SIZE);

}

World *Entities::getCurrentWorld() const {
    return currentWorld;
}

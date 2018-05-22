#include "Entities.h"
#include "../States/StateGame.h"


Entities::Entities(World *world, unsigned int id)
	: currentWorld(world)
	, id(id)
{
	onMap.setFillColor(sf::Color::Yellow);
	onMap.setRadius(50);
	onMap.setOrigin(sf::Vector2f(50, 50));

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

sf::Vector2f Entities::getWorldPos()
{
	sf::Vector2f position = getPosition();
	return sf::Vector2f(position.x / StateGame::TILE_SIZE, position.y / StateGame::TILE_SIZE);
}


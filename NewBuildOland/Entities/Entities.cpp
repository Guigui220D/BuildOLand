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

void Entities::drawMore(sf::RenderWindow& window)
{}

std::vector<unsigned char> Entities::getBeginningBytes(int code)
{
    std::vector<unsigned char> bytes;
    //Code
    bytes.push_back((code & 0x000000FF) << 0);
    bytes.push_back((code & 0x0000FF00) << 8);
    bytes.push_back((code & 0x00FF0000) << 16);
    bytes.push_back((code & 0xFF000000) << 24);
    //Pos x
    union
    {
        float f;
        int i;
    } posX;
    posX.f = getPosition().x;
    bytes.push_back((posX.i & 0x000000FF) << 0);
    bytes.push_back((posX.i & 0x0000FF00) << 8);
    bytes.push_back((posX.i & 0x00FF0000) << 16);
    bytes.push_back((posX.i & 0xFF000000) << 24);
    //Pos y
    union
    {
        float f;
        int i;
    } posY;
    posY.f = getPosition().y;
    bytes.push_back((posY.i & 0x000000FF) << 0);
    bytes.push_back((posY.i & 0x0000FF00) << 8);
    bytes.push_back((posY.i & 0x00FF0000) << 16);
    bytes.push_back((posY.i & 0xFF000000) << 24);
    return bytes;
}


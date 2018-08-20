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
    union
    {
        int i;
        unsigned char bytes[4];
    } codeu;
    codeu.i = code;
    bytes.push_back(codeu.bytes[0]);
    bytes.push_back(codeu.bytes[1]);
    bytes.push_back(codeu.bytes[2]);
    bytes.push_back(codeu.bytes[3]);
    //Pos x
    union
    {
        float f;
        unsigned char bytes[4];
    } posX;
    posX.f = getPosition().x;
    bytes.push_back(posX.bytes[0]);
    bytes.push_back(posX.bytes[1]);
    bytes.push_back(posX.bytes[2]);
    bytes.push_back(posX.bytes[3]);
    //Pos y
    union
    {
        float f;
        unsigned char bytes[4];
    } posY;
    posY.f = getPosition().y;
    bytes.push_back(posY.bytes[0]);
    bytes.push_back(posY.bytes[1]);
    bytes.push_back(posY.bytes[2]);
    bytes.push_back(posY.bytes[3]);
    return bytes;
}


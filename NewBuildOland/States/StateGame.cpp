#include "stdafx.h"
#include "StateGame.h"
#include "../Worlds/FlatWorld.h"
#include <iostream>

StateGame::StateGame(Game& game)
	: StateBase(game),
	circle(100.0f)
{
	//Set the world
	currentWorld = new FlatWorld(game);
	tileset = TestTileSet();
	circle.setFillColor(sf::Color::Red);
}

void StateGame::handleInput() {

}

void StateGame::update(float dt) {

}

void StateGame::draw(sf::RenderWindow &window) {
	//Set the right view for world drawing
	window.setView(game->getWorldView());
	//Get world size
	sf::Vector2u size = currentWorld->getSize();
	//Create a rectangle for drawing
	sf::RectangleShape draw = sf::RectangleShape();
	draw.setSize(sf::Vector2f(50, 50));
	draw.setTexture(tileset.getTexture());
	//Iterate through the world to draw each tile
	for (unsigned int x = 0; x < size.x; x++)
	{
		for (unsigned int y = 0; y < size.y; y++)
		{
			//Not working : the tileset.getGroundRect method seems to return a (0, 0, 0, 0) rectangle
			draw.setTextureRect(tileset.getGroundRect(currentWorld->getGroundId(sf::Vector2u(x, y))));
			draw.setPosition(x * 55, y * 55);	//This should be *50 but for testing it's *55 to see each tile individually
			window.draw(draw);
		}
	}
	window.draw(circle);
	
}

void StateGame::setWorld(World &world) {
	//We delete the old world
	//as we will be changing the pointer's adress
	delete currentWorld;

	//And load the new world
	currentWorld = &world;
}

StateGame::~StateGame()
{
	//We delete pointers to prevent memory leaks
	delete currentWorld;
}
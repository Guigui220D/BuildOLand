#include "stdafx.h"
#include "StateGame.h"
#include "../Worlds/FlatWorld.h"
#include <iostream>
#include "../Utils/TileSet.h"

StateGame::StateGame(Game& game)
	: StateBase(game),
	circle(100.0f)
{
	//Set the world
	currentWorld = new FlatWorld(game);
	tileset;
	circle.setFillColor(sf::Color::Red);
	mapView = View();
	mapView.setViewport(sf::FloatRect(0.70f, 0.05f, 0.25f, 0.25f));
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
	draw.setSize(sf::Vector2f(80, 80));
	draw.setTexture(tileset.getTexture());
	//Iterate through the world to draw each tile
	for (unsigned int x = 0; x < size.x; x++)
	{
		for (unsigned int y = 0; y < size.y; y++)
		{			
			draw.setTextureRect(tileset.getGroundRect(currentWorld->getGroundId(sf::Vector2u(x, y))));
			draw.setPosition(x * 80, y * 80);
			window.draw(draw);
		}
	}
	window.draw(circle);
	//Draw the map
	window.setView(game->getGuiView());
	//This is just for proof of concept, and will be optimized later
	sf::RectangleShape map = sf::RectangleShape();
	map.setFillColor(sf::Color::Black);
	map.setOutlineColor(sf::Color(255, 255, 0));
	map.setOutlineThickness(0.005f);
	map.setPosition(0.70f, 0.05f);
	map.setSize(sf::Vector2f(0.25f, 0.25f));
	mapView.setSize(game->getWorldView().getSize());
	mapView.zoom(2);
	window.draw(map);
	window.setView(mapView);
	sf::RectangleShape mapdraw = sf::RectangleShape();
	mapdraw.setSize(sf::Vector2f(80, 80));
	//Same method
	for (unsigned int x = 0; x < size.x; x++)
	{
		for (unsigned int y = 0; y < size.y; y++)
		{
			mapdraw.setFillColor(tileset.getMapPixel(currentWorld->getGroundId(sf::Vector2u(x, y))));
			mapdraw.setPosition(x * 80, y * 80);
			window.draw(mapdraw);
		}
	}
}

sf::View& StateGame::getMapView()
{
	return mapView;
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
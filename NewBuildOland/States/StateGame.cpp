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
	mapView.setViewport(sf::FloatRect(0.74f, 0.01f, 0.25f, 0.25f));
	mapFrame = sf::RectangleShape();
	mapFrame.setFillColor(sf::Color::Black);
	mapFrame.setOutlineColor(sf::Color(255, 255, 0));
	mapFrame.setOutlineThickness(0.005f);
	mapFrame.setPosition(mapView.getViewport().left, mapView.getViewport().top);
	mapFrame.setSize(sf::Vector2f(mapView.getViewport().width, mapView.getViewport().height));
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
	window.draw(mapFrame);
	mapView.setSize(game->getWorldView().getSize());
	mapView.zoom(3);
	mapView.setCenter(game->getWorldView().getCenter());
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
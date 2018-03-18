#include "stdafx.h"
#include "StateGame.h"
#include "../Worlds/FlatWorld.h"
#include <iostream>
#include "../Utils/TileSet.h"

StateGame::StateGame(Game& game)
	: StateBase(game)
{
	//Set the world
	currentWorld = new FlatWorld(game);
	tileset;

	mapView = View();
	mapView.setViewport(sf::FloatRect(0.74f, 0.01f, 0.25f, 0.25f));
	mapFrame = sf::RectangleShape();
	mapFrame.setFillColor(sf::Color::Black);
	mapFrame.setOutlineColor(sf::Color(255, 255, 0));
	mapFrame.setOutlineThickness(0.005f);
	mapFrame.setPosition(mapView.getViewport().left, mapView.getViewport().top);
	mapFrame.setSize(sf::Vector2f(mapView.getViewport().width, mapView.getViewport().height));

	worldDraw = sf::RectangleShape();
	worldDraw.setSize(sf::Vector2f(80, 80));
	worldDraw.setTexture(tileset.getTexture());

	mapDraw = sf::RectangleShape();
	mapDraw.setSize(sf::Vector2f(80, 80));

	player = Player();
	cameraFollow = &player;
}

void StateGame::handleInput() {

	//Temporary, for testing
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		int playerX = roundf(player.getPosition().x / 80);
		int playerY = roundf(player.getPosition().y / 80);

		if (currentWorld->getBlockId(sf::Vector2u(playerX, playerY)) != 1) {
			currentWorld->setBlockId(sf::Vector2u(playerX, playerY), 1);
			currentWorld->saveWorld(); //Only temporary, later saveWorld after x sec or when closing
		}
	}
}

void StateGame::update(float dt) {
	player.update(dt);
	game->getWorldView().setCenter(cameraFollow->getPosition());
}

void StateGame::draw(sf::RenderWindow &window) {
	//Set the right view for world drawing
	window.setView(game->getWorldView());
	//Get world size
	sf::Vector2u size = currentWorld->getWorldSize();
	//Create a rectangle for drawing
	
	//Iterate through the world to draw each tile
	for (unsigned int x = 0; x < size.x; x++)
	{
		for (unsigned int y = 0; y < size.y; y++)
		{			
			//Draw the ground
			worldDraw.setPosition(x * 80, y * 80);
			worldDraw.setTextureRect(tileset.getGroundRect(currentWorld->getGroundId(sf::Vector2u(x, y))));
			window.draw(worldDraw);
			//Draw the block shadow
			worldDraw.setTextureRect(tileset.getBlockRect(currentWorld->getBlockId(sf::Vector2u(x, y))));
			worldDraw.setFillColor(sf::Color::Black);
			worldDraw.setPosition(x * 80 - 5, y * 80 + 5);
			window.draw(worldDraw);
			//Draw the block
			worldDraw.setFillColor(sf::Color::White);
			worldDraw.setPosition(x * 80, y * 80);
			window.draw(worldDraw);
		}
	}
	window.draw(player);
	//Draw the map
	window.setView(game->getGuiView());	
	window.draw(mapFrame);
	mapView.setSize(game->getWorldView().getSize());
	mapView.zoom(3);
	mapView.setCenter(game->getWorldView().getCenter());
	window.setView(mapView);
	//Same method
	for (unsigned int x = 0; x < size.x; x++)
	{
		for (unsigned int y = 0; y < size.y; y++)
		{
			mapDraw.setFillColor(tileset.getMapPixel(currentWorld->getGroundId(sf::Vector2u(x, y)), currentWorld->getBlockId(sf::Vector2u(x, y))));
			mapDraw.setPosition(x * 80, y * 80);
			window.draw(mapDraw);
		}
	}
	window.draw(*player.getOnMap());
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
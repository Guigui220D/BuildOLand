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
	worldDraw.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	worldDraw.setOrigin(sf::Vector2f(TILE_SIZE / 2.0f, TILE_SIZE / 2.0f));
	worldDraw.setTexture(tileset.getTexture());

	mapDraw = sf::RectangleShape();
	mapDraw.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	mapDraw.setOrigin(sf::Vector2f(TILE_SIZE / 2.0f, TILE_SIZE / 2.0f));

	player = Player(currentWorld);
	cameraFollow = &player;
}

void StateGame::handleInput() {

	//Temporary, for testing
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Gets the mouse pos in the window
		Vector2i pos = sf::Mouse::getPosition(game->getWindow());
		if (pos.x >= 0 && pos.y >= 0 && pos.x < game->getWindow().getSize().x && pos.y < game->getWindow().getSize().y)
		{
			game->getWindow().setView(game->getWorldView());
			Vector2f posInView = game->getWindow().mapPixelToCoords(pos);
			Vector2f diff = posInView - player.getPosition();
			if (sqrt(diff.x * diff.x + diff.y * diff.y) <= 240)
			{
				int clickX = roundf(posInView.x / TILE_SIZE);
				int clickY = roundf(posInView.y / TILE_SIZE);
				if (currentWorld->getBlockId(sf::Vector2u(clickX, clickY)) != 1) {
					currentWorld->setBlockId(sf::Vector2u(clickX, clickY), 1);
					currentWorld->saveWorld(); //Only temporary, later saveWorld after x sec or when closing
				}
			}
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		//Gets the mouse pos in the window
		Vector2i pos = sf::Mouse::getPosition(game->getWindow());
		if (pos.x >= 0 && pos.y >= 0 && pos.x < game->getWindow().getSize().x && pos.y < game->getWindow().getSize().y)
		{
			game->getWindow().setView(game->getWorldView());
			Vector2f posInView = game->getWindow().mapPixelToCoords(pos);
			Vector2f diff = posInView - player.getPosition();
			if (sqrt(diff.x * diff.x + diff.y * diff.y) <= 240)
			{
				int clickX = roundf(posInView.x / TILE_SIZE);
				int clickY = roundf(posInView.y / TILE_SIZE);
				if (currentWorld->getBlockId(sf::Vector2u(clickX, clickY)) != 0) {
					currentWorld->setBlockId(sf::Vector2u(clickX, clickY), 0);
					currentWorld->saveWorld(); //Only temporary, later saveWorld after x sec or when closing
				}
			}
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
			worldDraw.setPosition(x * TILE_SIZE, y * TILE_SIZE);
			worldDraw.setTextureRect(tileset.getGroundRect(currentWorld->getGroundId(sf::Vector2u(x, y))));
			window.draw(worldDraw);
			//Draw the block shadow
			worldDraw.setTextureRect(tileset.getBlockRect(currentWorld->getBlockId(sf::Vector2u(x, y))));
			worldDraw.setFillColor(sf::Color::Black);
			worldDraw.setPosition(x * TILE_SIZE - 5, y * TILE_SIZE + 5);
			window.draw(worldDraw);
			//Draw the block
			worldDraw.setFillColor(sf::Color::White);
			worldDraw.setPosition(x * TILE_SIZE, y * TILE_SIZE);
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
			mapDraw.setPosition(x * TILE_SIZE, y * TILE_SIZE);
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

unsigned int StateGame::getTileSize()
{
	return TILE_SIZE;
}

StateGame::~StateGame()
{
	//We delete pointers to prevent memory leaks
	delete currentWorld;
}
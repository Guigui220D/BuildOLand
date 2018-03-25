#include "stdafx.h"
#include "StateGame.h"
#include "../Worlds/FlatWorld.h"
#include "../Worlds/MazeWorld.h"
#include <iostream>
#include "../Events/Events.h"

StateGame::StateGame(Game& game)
	: StateBase(game)
{
	//Set the world
	currentWorld = new MazeWorld(game);
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
	worldDraw.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT));
	worldDraw.setOrigin(sf::Vector2f(TILE_SIZE / 2.0f, TILE_SIZE / 2.0f));
	worldDraw.setTexture(tileset.getTexture());

	mapDraw = sf::RectangleShape();
	mapDraw.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT));
	mapDraw.setOrigin(sf::Vector2f(TILE_SIZE / 2.0f, TILE_SIZE / 2.0f));

	pointer = sf::RectangleShape();
	pointer.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT));
	pointer.setOrigin(sf::Vector2f(TILE_SIZE / 2.0f, TILE_SIZE / 2.0f));
	pointer.setTexture(tileset.getTexture());
	pointer.setTextureRect(sf::IntRect(128, 32, 32, 32));
	
	player = Player(*currentWorld);
	cameraFollow = &player;
}

void StateGame::handleInput() {

	//Temporary, for testing
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Gets the mouse pos in the window
		Vector2i pos = sf::Mouse::getPosition(game->getWindow());
		if (pos.x >= 0 && pos.y >= 0 && (unsigned)pos.x < game->getWindow().getSize().x && (unsigned)pos.y < game->getWindow().getSize().y)
		{
			game->getWindow().setView(game->getWorldView());
			Vector2f posInView = game->getWindow().mapPixelToCoords(pos);
			Vector2f diff = posInView - player.getPosition();
			if (sqrt(diff.x * diff.x + diff.y * diff.y) <= 240)
			{
				int clickX = (int)roundf(posInView.x / TILE_SIZE);
				int clickY = (int)roundf(posInView.y / TILE_SIZE);
				if (currentWorld->getBlockId(sf::Vector2u(clickX, clickY)) != 1) {
					Events::OnBlockBuild(BlockBuildEvent(sf::Vector2i(clickX, clickY), 1, player));
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
		if (pos.x >= 0 && pos.y >= 0 && (unsigned)pos.x < game->getWindow().getSize().x && (unsigned)pos.y < game->getWindow().getSize().y)
		{
			game->getWindow().setView(game->getWorldView());
			Vector2f posInView = game->getWindow().mapPixelToCoords(pos);
			Vector2f diff = posInView - player.getPosition();
			if (sqrt(diff.x * diff.x + diff.y * diff.y) <= 240)
			{
				int clickX = (int)roundf(posInView.x / TILE_SIZE);
				int clickY = (int)roundf(posInView.y / TILE_SIZE);
				if (currentWorld->getBlockId(sf::Vector2u(clickX, clickY)) != 0) {
					Events::OnBlockBreak(BlockBreakEvent(sf::Vector2i(clickX, clickY), currentWorld->getBlockId(sf::Vector2u(clickX, clickY)), player));
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
	for (int x = (int)(player.getPosition().x / TILE_SIZE) - 14; x < (int)(player.getPosition().x / TILE_SIZE) + 14; x++)
	{
		for (int y = (int)(player.getPosition().y / TILE_SIZE) - 14; y < (int)(player.getPosition().y / TILE_SIZE) + 14; y++)
		{		
			//Draw the ground
			worldDraw.setPosition(TILE_SIZE_FLOAT * x, TILE_SIZE_FLOAT * y);
			worldDraw.setTextureRect(tileset.getGroundRect(currentWorld->getGroundId(sf::Vector2u(x, y))));
			window.draw(worldDraw);
			//Draw the block shadow
			worldDraw.setTextureRect(tileset.getBlockRect(currentWorld->getBlockId(sf::Vector2u(x, y))));
			worldDraw.setFillColor(sf::Color::Black);
			worldDraw.setPosition(TILE_SIZE_FLOAT * x - 5, TILE_SIZE_FLOAT * y + 5);
			window.draw(worldDraw);
			//Draw the block
			worldDraw.setFillColor(sf::Color::White);
			worldDraw.setPosition(TILE_SIZE_FLOAT * x, TILE_SIZE_FLOAT * y);
			window.draw(worldDraw);					
		}
	}

	//Draw block highlighter
	Vector2i pos = sf::Mouse::getPosition(game->getWindow());
	if (pos.x >= 0 && pos.y >= 0 && (unsigned)pos.x < game->getWindow().getSize().x && (unsigned)pos.y < game->getWindow().getSize().y)
	{		
		Vector2f posInView = game->getWindow().mapPixelToCoords(pos);		
		Vector2f diff = posInView - player.getPosition();
		int clickX = (int)roundf(posInView.x / TILE_SIZE);
		int clickY = (int)roundf(posInView.y / TILE_SIZE);
		if (sqrt(diff.x * diff.x + diff.y * diff.y) <= 240)
		{			
			pointer.setFillColor(sf::Color::White);
		}
		else
		{
			pointer.setFillColor(sf::Color::Red);
		}
		pointer.setPosition(sf::Vector2f(clickX * TILE_SIZE, clickY * TILE_SIZE));
		window.draw(pointer);
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
			mapDraw.setPosition(TILE_SIZE_FLOAT * x, TILE_SIZE_FLOAT * y);
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
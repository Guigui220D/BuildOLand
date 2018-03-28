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
	pointer.setTextureRect(sf::IntRect(136, 34, 32, 32));

	mouse = sf::RectangleShape();
	mouse.setSize(sf::Vector2f(TILE_SIZE_FLOAT / 3, TILE_SIZE_FLOAT / 3));
	Texture* t = new Texture();
	(*t).loadFromFile("Res/hand.png");
	mouse.setTexture(t);
	
	player = Player(*currentWorld);
	cameraFollow = &player;

	//Temporary, for save button
	currentWorld->setBlockId(sf::Vector2u(0, 0), 4);
}

void StateGame::handleInput() {
	//Temporary, for testing
	//This is crappy code
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!leftClicking)
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
					if (clickX >= 0 && clickY >= 0 && currentWorld->getBlockId(sf::Vector2u(clickX, clickY)) == 0) {
						Events::OnBlockBuild(BlockBuildEvent(sf::Vector2u(clickX, clickY), 1, player, this));
						currentWorld->setBlockId(sf::Vector2u(clickX, clickY), 1);
						//currentWorld->saveWorld(); //Only temporary, later saveWorld after x sec or when closing
					}
				}
			}
		}
		leftClicking = true;
	}
	else
	{
		leftClicking = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!rightClicking)
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
					if (clickX >= 0 && clickY >= 0 && currentWorld->getBlockId(sf::Vector2u(clickX, clickY)) != 0) {
						unsigned short oldBlock = currentWorld->getBlockId(sf::Vector2u(clickX, clickY));
						currentWorld->setBlockId(sf::Vector2u(clickX, clickY), 0);
						Events::OnBlockBreak(BlockBreakEvent(sf::Vector2u(clickX, clickY), oldBlock, player, this));
						//currentWorld->saveWorld(); //Only temporary, later saveWorld after x sec or when closing
					}
				}
			}
		}
		rightClicking = true;
	}
	else
	{
		rightClicking = false;
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
	if (game->getWindow().hasFocus())
	{
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

	if (game->getWindow().hasFocus())
	{
		window.setView(game->getWorldView());
		Vector2i mousepos = sf::Mouse::getPosition(game->getWindow());
		Vector2f onGui = game->getWindow().mapPixelToCoords(mousepos);
		mouse.setPosition(sf::Vector2f(onGui.x, onGui.y));
		window.draw(mouse);
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

void StateGame::setClicks()
{
	rightClicking = true;
	leftClicking = true;
}

World * StateGame::getWorld()
{
	return currentWorld;
}

StateGame::~StateGame()
{
	//We delete pointers to prevent memory leaks
	delete currentWorld;
}
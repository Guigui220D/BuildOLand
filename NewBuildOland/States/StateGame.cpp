#include "stdafx.h"
#include "StateGame.h"
#include "../Worlds/FlatWorld.h"
#include "../Worlds/MazeWorld.h"
#include <iostream>
#include "../Events/EventManager.h"
#include "SFML/Audio/SoundBuffer.hpp"
#include "../Entities/StaticObjects/TestObject.h"

StateGame::StateGame(Game& game)
	: StateBase(game)
{
	//Set the world
	currentWorld = new MazeWorld(*this);
	tileset;

	//Init the tileset to the event manager
	EventManager::tileset = &tileset;

	//Init the sound manager
	soundManager;
	sf::Music* backgroundMusic = soundManager.getMusic("fantasymusic.ogg");
	backgroundMusic->setVolume(20);
	backgroundMusic->play();
	sf::Music* backgroundAmbiance = soundManager.getMusic("forest-ambiance.ogg");
	backgroundAmbiance->setVolume(30);
	backgroundAmbiance->setLoop(true);
	backgroundAmbiance->play();

	//Init all the drawers
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

	//Setup the entity lists
	entities = std::vector<Entities>();
	blockEntities = std::vector<BlockEntity>();

	//Temporary for entity testing
	entities.push_back(TestObject());

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
						EventManager::OnBlockBuild(BlockBuildEvent(sf::Vector2u(clickX, clickY), blockPlaceId, (&player), this));
						currentWorld->setBlockId(sf::Vector2u(clickX, clickY), blockPlaceId);
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
						EventManager::OnBlockBreak(BlockBreakEvent(sf::Vector2u(clickX, clickY), oldBlock, (&player), this));
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

	//To change the block being placed (Temporary)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
		if (blockPlaceId < tileset.getTotalBlockNb() - 1 && !isPlaceKeyPressed) {
			blockPlaceId++;
			std::cout << "BLOCK " << tileset.getBlockById(blockPlaceId)->getName() << " SELECTED " << std::endl;
		}
		isPlaceKeyPressed = true;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
		if(blockPlaceId > 1 && !isPlaceKeyPressed) {
			blockPlaceId--;
			std::cout << "BLOCK " << tileset.getBlockById(blockPlaceId)->getName() << " SELECTED " << std::endl;
		}
		isPlaceKeyPressed = true;
	} else {
		isPlaceKeyPressed = false;
	}
}

void StateGame::update(float dt) {
	player.update(dt);
	for (int i = 0; i < blockEntities.size(); i++)
		blockEntities[i].update(dt);
	for (int i = 0; i < entities.size(); i++)
		entities[i].update(dt);
	game->getWorldView().setCenter(cameraFollow->getPosition());
}

void StateGame::draw(sf::RenderWindow &window) {
	//Set the right view for world drawing
	window.setView(game->getWorldView());
	//Get world size
	sf::Vector2u size = currentWorld->getWorldSize();
	//Create a rectangle for drawing
	
	//Iterate through the world to draw each tile
	//Draw the gound
	worldDraw.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT));
	for (int x = (int)(player.getPosition().x / TILE_SIZE) - 14; x < (int)(player.getPosition().x / TILE_SIZE) + 14; x++)
	{
		for (int y = (int)(player.getPosition().y / TILE_SIZE) - 14; y < (int)(player.getPosition().y / TILE_SIZE) + 14; y++)
		{		
			//Draw the ground
			unsigned short groundId = currentWorld->getGroundId(sf::Vector2u(x, y));
			unsigned short blockId = currentWorld->getBlockId(sf::Vector2u(x, y));
			worldDraw.setPosition(TILE_SIZE_FLOAT * x, TILE_SIZE_FLOAT * y);
			worldDraw.setTextureRect(tileset.getGroundRect(groundId));
			window.draw(worldDraw);	
			if (!tileset.getBlockById(blockId)->hasVolume())
			{
				worldDraw.setTextureRect(tileset.getBlockRect(blockId));
				window.draw(worldDraw);
			}
		}
	}
	//Draw the block's front sides
	worldDraw.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT /2));
	for (int x = (int)(player.getPosition().x / TILE_SIZE) - 14; x < (int)(player.getPosition().x / TILE_SIZE) + 14; x++)
	{
		for (int y = (int)(player.getPosition().y / TILE_SIZE) - 14; y < (int)(player.getPosition().y / TILE_SIZE) + 14; y++)
		{
			//Draw the block front
			unsigned short blockId = currentWorld->getBlockId(sf::Vector2u(x, y));
			if (tileset.getBlockById(blockId)->hasVolume())
			{
				worldDraw.setTextureRect(tileset.getBlockSideRect(blockId));
				worldDraw.setFillColor(tileset.getSideTint(blockId));
				worldDraw.setPosition(TILE_SIZE_FLOAT * x, TILE_SIZE_FLOAT * y + TILE_SIZE_FLOAT / 2);
				window.draw(worldDraw);
			}
		}
	}
	//Draw all entities
	for (int i = 0; i < blockEntities.size(); i++)
		window.draw(blockEntities[i]);
	for (int i = 0; i < entities.size(); i++)
		window.draw(entities[i]);
	window.draw(player);
	//Draw the actual blocks
	worldDraw.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT));
	for (int x = (int)(player.getPosition().x / TILE_SIZE) - 14; x < (int)(player.getPosition().x / TILE_SIZE) + 14; x++)
	{
		for (int y = (int)(player.getPosition().y / TILE_SIZE) - 14; y < (int)(player.getPosition().y / TILE_SIZE) + 14; y++)
		{
			//Draw the block
			unsigned short blockId = currentWorld->getBlockId(sf::Vector2u(x, y));
			if (tileset.getBlockById(blockId)->hasVolume())
			{
				worldDraw.setTextureRect(tileset.getBlockRect(blockId));
				worldDraw.setFillColor(sf::Color::White);
				worldDraw.setPosition(TILE_SIZE_FLOAT * x, TILE_SIZE_FLOAT * y - TILE_SIZE_FLOAT / 2);
				window.draw(worldDraw);
			}
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
	//Draw entities on map
	for (int i = 0; i < entities.size(); i++)
		window.draw(*entities[i].getOnMap());
	window.draw(*player.getOnMap());

	window.setView(game->getWorldView());
	Vector2i mousepos = sf::Mouse::getPosition(game->getWindow());
	Vector2f onGui = game->getWindow().mapPixelToCoords(mousepos);
	mouse.setPosition(sf::Vector2f(onGui.x, onGui.y));
	window.draw(mouse);
}

sf::View& StateGame::getMapView()
{
	return mapView;
}

TileSet* StateGame::getTileset() {
	return &tileset;
}

void StateGame::setWorld(World &world) {
	//Save the old world
	currentWorld->saveWorld();
	//We delete the old world
	//as we will be changing the pointer's adress
	currentWorld->setDeleted();
	delete currentWorld;

	//And load the new world
	currentWorld = &world;

	//Set the current world for the player
	player.setCurrentWorld(currentWorld);
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

SoundManager* StateGame::getSoundManager()
{
	return &soundManager;
}

StateGame::~StateGame()
{
	//We delete pointers to prevent memory leaks
	delete currentWorld;
}
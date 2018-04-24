#include "StateGame.h"
#include "../Worlds/FlatWorld.h"
#include "../Worlds/MazeWorld.h"
#include <iostream>
#include "../Events/EventManager.h"
#include "SFML/Audio/SoundBuffer.hpp"
#include "../Entities/StaticObjects/TestObject.h"
#include "../Gui/FpsCounter.h"
#include "../Gui/InventoryGui.h"
#include <math.h>


StateGame::StateGame(Game& game)
	: StateBase(game) {
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

	player = Player(currentWorld);
	cameraFollow = &player;

	//Setup the entity lists
	entities = std::vector<Entities>();
	entities.push_back(TestObject());

	//Setup the gui
	gui = std::vector<std::unique_ptr<Gui>>();
    gui.push_back(std::unique_ptr<Gui>(new FpsCounter(this)));
    gui.push_back(std::unique_ptr<Gui>(new InventoryGui(this, player.getInventory(), &inventoryCursorId)));

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
						//Remove block from player Inventory
						Inventory *inventory = player.getInventory();
						ItemStack *selectedItemStack = inventory->getItem(inventoryCursorId);
						Item *selectedItem = selectedItemStack->getItem();

                        //If it isn'text empty, and is a block
                        if(!selectedItemStack->isEmpty() && selectedItem->isPlaceable() && !selectedItem->isGround()) {
                            //We remove an item (that was placed)
							selectedItemStack->remove();
							//Get the id from the tileset
							unsigned short blockId = tileset.getBlockIdByName(selectedItem->getName());

							//Send an event that the block was placed
							EventManager::OnBlockBuild(BlockBuildEvent(sf::Vector2u(clickX, clickY), blockId, (&player), this));
							//Place the block
							currentWorld->setBlockId(sf::Vector2u(clickX, clickY), blockId);

						}

						//currentWorld->saveWorld();
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
                    //Get the block that was clicked on
                    unsigned short selectedBlockId = currentWorld->getBlockId(sf::Vector2u(clickX, clickY));

                    if (clickX >= 0 && clickY >= 0 && selectedBlockId  != 0) {

						currentWorld->setBlockId(sf::Vector2u(clickX, clickY), 0);
						EventManager::OnBlockBreak(BlockBreakEvent(sf::Vector2u(clickX, clickY), selectedBlockId, (&player), this));

                        //Add the block to the inventory
                        player.getInventory()->addItem(ItemStack(tileset.getBlockById(selectedBlockId)));

						//currentWorld->saveWorld();
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
		if (!isPlaceKeyPressed) {
			inventoryCursorId = inventoryCursorId >= 9 ? 0 : inventoryCursorId + 1;
		}
		isPlaceKeyPressed = true;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
		if(!isPlaceKeyPressed) {
            inventoryCursorId = inventoryCursorId <= 0 ? 9 : inventoryCursorId - 1;
		}
		isPlaceKeyPressed = true;
	} else {
		isPlaceKeyPressed = false;
	}
}

void StateGame::update(float dt) {
	player.update(dt);
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

	window.setView(game->getGuiView());

	for (int i = 0; i < gui.size(); i++)
    {
        gui[i]->act();
        window.draw(*gui[i]);
        gui[i]->drawMore(window);
    }

	window.setView(game->getWorldView());
	Vector2i mousepos = sf::Mouse::getPosition(game->getWindow());
	Vector2f onGui = game->getWindow().mapPixelToCoords(mousepos);
	mouse.setPosition(sf::Vector2f(onGui.x, onGui.y));
	window.draw(mouse);
}

sf::View& StateGame::getMapView() {
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

void StateGame::setClicks() {
	rightClicking = true;
	leftClicking = true;
}

World * StateGame::getWorld() {
	return currentWorld;
}

SoundManager* StateGame::getSoundManager() {
	return &soundManager;
}

StateGame::~StateGame() {
	//We delete pointers to prevent memory leaks
	delete currentWorld;
}

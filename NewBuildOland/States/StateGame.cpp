#include "StateGame.h"
#include "../Worlds/FlatWorld.h"
#include "../Worlds/MazeWorld.h"
#include "../Worlds/NetworkWorld.h"
#include <iostream>
#include "SFML/Audio/SoundBuffer.hpp"
#include "../Gui/FpsCounter.h"
#include "../Gui/InventoryGui.h"
#include <math.h>
#include <cstring>
#include <sstream>
#include "../Events/EventManager.h"


StateGame::StateGame(Game& game, bool online, std::string playerName, std::string addressInput)
	: StateBase(game)
	, nManager(this)
{
	game.getWindow().setMouseCursorVisible(false);

	onlineMode = online;
    char nick[16] = "Player";

	if (onlineMode)
    {
        //Username from string to char array
        for (int i = 0; i < 16; i++)
            nick[i] = 0;
        strcpy(nick, playerName.c_str());

        //Getting the url and port as separate variables
        std::string addressUrl;
        unsigned short addressPort;
        std::replace(addressInput.begin(), addressInput.end(), ':', ' ');  // replacing ':' by ' '
        std::stringstream addressStream(addressInput);
        addressStream >> addressUrl;
        addressStream >> addressPort;

        std::cout << addressUrl << ":"  << addressPort << std::endl;
        sf::IpAddress address(addressUrl);

        //Usinge the network manager to connect to the server
        std::cout << "Connected = " << nManager.connect(nick, address, 54321) << "\n";
        currentWorld = new NetworkWorld(*this);
    }
    else
    {
        currentWorld = new MazeWorld(*this);
    }

	//Init the tileset to the event manager
	EventManager::tileset = &tileset;
	EventManager::state = this;

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
	mapView.setSize(game.getWorldView().getSize());
	mapView.zoom(3);

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

    player = new Player(currentWorld, nick, nManager.getPlayerID());    //Player id should be 0 if it's offline
	player->init(0, 0);
	cameraFollow = player;

	//Setup the gui
	inventoryGui = new InventoryGui(this, player->getInventory(), &inventoryCursorId);
	chatGui = new ChatGui(this);

	gui = std::vector<std::unique_ptr<Gui>>();
	gui.push_back(std::unique_ptr<Gui>(new FpsCounter(this)));
	gui.push_back(std::unique_ptr<Gui>(inventoryGui));
	gui.push_back(std::unique_ptr<Gui>(chatGui));

}

void StateGame::handleInput() {
	//Temporary, for testing
	//This is crappy code
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
				Vector2f diff = posInView - player->getPosition();
				if (sqrt(diff.x * diff.x + diff.y * diff.y) <= 240)
				{
					int clickX = (int)roundf(posInView.x / TILE_SIZE);
					int clickY = (int)roundf(posInView.y / TILE_SIZE);

                    if (currentWorld->getBlockId(sf::Vector2i(clickX, clickY)) == 0)
                    {
                        //Remove block from player Inventory
                        Inventory *inventory = player->getInventory();
                        ItemStack *selectedItemStack = inventory->getItem(inventoryCursorId);
                        Item *selectedItem = selectedItemStack->getItem();

                            //If it isn't empty, and is a placeable
                        if(!selectedItemStack->isEmpty() && selectedItem->isPlaceable())
                        {
                            bool isGround = selectedItem->isGround();
                            //We remove an item (that was placed)
                            selectedItemStack->remove();
                            //Get the id from the tileset
                            unsigned short placeableId = isGround ? tileset.getGroundIdByName(selectedItem->getName())
                                                                    : tileset.getBlockIdByName(selectedItem->getName());
                            if(isGround)
                            {
                                //Get the old ground
                                unsigned short oldGroundId = currentWorld->getGroundId(sf::Vector2i(clickX, clickY));
                                //Send an event that the ground was placed
                                EventManager::OnGroundPlace(GroundPlaceEvent(sf::Vector2i(clickX, clickY), oldGroundId, placeableId, player, this));
                                //Place the ground
                                currentWorld->setGroundId(sf::Vector2i(clickX, clickY), placeableId);
                                //Add the old ground to the inventory (the one that you should get when you break it)
                                player->getInventory()->addItem(ItemStack(tileset.getGroundById(oldGroundId)->getGroundOnBreak(this)));

                            }
                            else
                            {
                                //Send an event that the block was placed
                                EventManager::OnBlockBuild(BlockBuildEvent(sf::Vector2i(clickX, clickY), placeableId, player, this));
                                //Place the block
                                currentWorld->setBlockId(sf::Vector2i(clickX, clickY), placeableId);
                            }
                            //And finally we update the inventory gui
                            inventoryGui->updateInventory();
                        }
                    }
                    else
                    {
                        EventManager::OnBlockInteract(BlockInteractEvent(sf::Vector2i(clickX, clickY), currentWorld->getBlockId(sf::Vector2i(clickX, clickY)), player, this));
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
				Vector2f diff = posInView - player->getPosition();
				if (sqrt(diff.x * diff.x + diff.y * diff.y) <= 240)
				{
					int clickX = (int)roundf(posInView.x / TILE_SIZE);
					int clickY = (int)roundf(posInView.y / TILE_SIZE);
                    //Get the block that was released on
                    unsigned short selectedBlockId = currentWorld->getBlockId(sf::Vector2i(clickX, clickY));

                    if (selectedBlockId  != 0)
                    {
                        currentWorld->setBlockId(sf::Vector2i(clickX, clickY), 0);
                        EventManager::OnBlockBreak(BlockBreakEvent(sf::Vector2i(clickX, clickY), selectedBlockId, player, this));

                        //Add the block to the inventory that you should get when you break it
                        player->getInventory()->addItem(ItemStack(tileset.getBlockById(selectedBlockId)->getBlockOnBreak(this)));
                        //And update the inventoryGui
                        inventoryGui->updateInventory();
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

	//To change the block being placed (Temporary)

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
		if (!isPlaceKeyPressed) {
			inventoryCursorId = inventoryCursorId >= inventoryGui->getInventorySlots() - 1 ? 0 : inventoryCursorId + 1;
		}
		isPlaceKeyPressed = true;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
		if(!isPlaceKeyPressed) {
            inventoryCursorId = inventoryCursorId <= 0 ? inventoryGui->getInventorySlots() - 1 : inventoryCursorId - 1;
		}
		isPlaceKeyPressed = true;
	} else {
		isPlaceKeyPressed = false;
	}


	//For showing the tchat writing bar
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		if(!chatGui->isActive()) {
			chatGui->setIsActive(true);
		}
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		if(chatGui->isActive()) {
			chatGui->setIsActive(false);
		}
	}

}

void StateGame::update(float dt, bool focused) {
    currentWorld->updateChunks();

    if (focused)
        player->update(dt);

	currentWorld->removeEntitiesThatNeedToBeRemoved();
	//Update the entities of the world

	for (int i = 0; i < currentWorld->getEntities().size(); i++)
		currentWorld->getEntities()[i]->update(dt);

	game->getWorldView().setCenter(cameraFollow->getPosition());

	//Update the GUI
	for (int i = 0; i < gui.size(); i++)
	{
		gui[i]->update(dt);
	}

}

void StateGame::draw(sf::RenderWindow &window) {
	//Set the right view for world drawing
	window.setView(game->getWorldView());
	//Create a rectangle for drawing

	//Iterate through the world to draw each tile
	//Draw the ground
	worldDraw.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT));
	for (int x = (int)(player->getPosition().x / TILE_SIZE) - 14; x < (int)(player->getPosition().x / TILE_SIZE) + 14; x++)
	{
		for (int y = (int)(player->getPosition().y / TILE_SIZE) - 14; y < (int)(player->getPosition().y / TILE_SIZE) + 14; y++)
		{
			//Draw the ground
			unsigned short groundId = currentWorld->getGroundId(sf::Vector2i(x, y));
			unsigned short blockId = currentWorld->getBlockId(sf::Vector2i(x, y));
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
	worldDraw.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT / 2));
	for (int x = (int)(player->getPosition().x / TILE_SIZE) - 14; x < (int)(player->getPosition().x / TILE_SIZE) + 14; x++)
	{
		for (int y = (int)(player->getPosition().y / TILE_SIZE) - 14; y < (int)(player->getPosition().y / TILE_SIZE) + 14; y++)
		{
			//Draw the block front
			unsigned short blockId = currentWorld->getBlockId(sf::Vector2i(x, y));
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
	for (int i = 0; i < currentWorld->getEntities().size(); i++)
        window.draw(*(currentWorld->getEntities()[i]));
	//And draw the player
	window.draw(*player);

	//Draw the actual blocks
	worldDraw.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT));
	for (int x = (int)(player->getPosition().x / TILE_SIZE) - 14; x < (int)(player->getPosition().x / TILE_SIZE) + 14; x++)
	{
		for (int y = (int)(player->getPosition().y / TILE_SIZE) - 14; y < (int)(player->getPosition().y / TILE_SIZE) + 14; y++)
		{
			//Draw the block
			unsigned short blockId = currentWorld->getBlockId(sf::Vector2i(x, y));
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
			Vector2f diff = posInView - player->getPosition();
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

	//Draw more for entities
	for (int i = 0; i < currentWorld->getEntities().size(); i++)
        (*currentWorld->getEntities()[i]).drawMore(window);
    player->drawMore(window);

	//Draw the map
	mapView.setCenter(game->getWorldView().getCenter());
	window.setView(mapView);
	//Same method
	for (int x = (int)(player->getPosition().x / TILE_SIZE) - 24; x < (int)(player->getPosition().x / TILE_SIZE) + 24; x++)
	{
		for (int y = (int)(player->getPosition().y / TILE_SIZE) - 14; y < (int)(player->getPosition().y / TILE_SIZE) + 14; y++)
		{
			mapDraw.setFillColor(tileset.getMapPixel(currentWorld->getGroundId(sf::Vector2i(x, y)), currentWorld->getBlockId(sf::Vector2i(x, y))));
			mapDraw.setPosition(TILE_SIZE_FLOAT * x, TILE_SIZE_FLOAT * y);
			window.draw(mapDraw);
		}
	}
	//Draw entities on map
	for (int i = 0; i < currentWorld->getEntities().size(); i++)
		window.draw(*(currentWorld->getEntities()[i]->getOnMap()));
	window.draw(*player->getOnMap());
	window.draw(mapFrame);

    //Draw the gui
	window.setView(game->getGuiView());

	for (int i = 0; i < gui.size(); i++)
    {
		gui[i]->draw(window);
    }
    //Draw the mouse
	window.setView(game->getWorldView());
	Vector2i mousepos = sf::Mouse::getPosition(game->getWindow());
	Vector2f onGui = game->getWindow().mapPixelToCoords(mousepos);
	mouse.setPosition(sf::Vector2f(onGui.x, onGui.y));
	window.draw(mouse);
}

void StateGame::setWorld(World &world) {
	//We delete the old world
	//as we will be changing the pointer's adress
	currentWorld->setDeleted();
	delete currentWorld;

	//And load the new world
	currentWorld = &world;

	//Set the current world for the player
	player->setCurrentWorld(currentWorld);
}

StateGame::~StateGame() {
	//We delete pointers to prevent memory leaks
	delete currentWorld;
	std::cout << "Stategame delete\n";
}

void StateGame::handleEvent(sf::Event &event) {

    switch (event.type) {
        //RESIZE EVENT
        case sf::Event::Resized:
            //Send the event to all gui elements
            for (unsigned int i = 0; i < gui.size(); i++)
            {
                gui[i]->eventResize();
            }
            break;

        //SCROLL EVENT
        case sf::Event::MouseWheelScrolled:
            //Change the position of the cursor
            if(event.mouseWheelScroll.delta < 0) {
                inventoryCursorId = inventoryCursorId >= inventoryGui->getInventorySlots() - 1 ? 0 : inventoryCursorId + 1;
            } else {
                inventoryCursorId = inventoryCursorId <= 0 ? inventoryGui->getInventorySlots() - 1 : inventoryCursorId - 1;
            }

            break;

		case sf::Event::TextEntered:
			chatGui->eventInput(event.text.unicode);
			break;
    }

}

void StateGame::onStop()
{
    if (onlineMode)
        nManager.disconnect();
}

sf::View& StateGame::getGuiView() { return game->getGuiView(); };


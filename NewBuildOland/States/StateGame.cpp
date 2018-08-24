#include "StateGame.h"

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
    initAssets();

	game.getWindow().setMouseCursorVisible(false);

	onlineMode = online;
    char nick[16] = "Player";

	if (onlineMode)
    {
        //Username from string to char array
        strcpy(nick, playerName.c_str());
        for (int i = playerName.size(); i < 16; i++)
            nick[i] = 0;

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
        currentWorld = new World(*this);
    }

	//Init the tileset to the event manager
	EventManager::tileset = &tileset;
	EventManager::state = this;

	sf::Music* backgroundMusic = assetManager.getMusic("FANTASY_MUSIC");
	backgroundMusic->setVolume(20);
	backgroundMusic->play();
	sf::Music* backgroundAmbiance = assetManager.getMusic("BIRDS_CHIPPING");
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
	mouse.setTexture(assetManager.getTexture("HAND"));

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

void StateGame::initAssets()
{
    assetManager.loadMusicFromFile("fantasymusic.ogg", "FANTASY_MUSIC");
    assetManager.loadMusicFromFile("forest-ambiance.ogg", "BIRDS_CHIPPING");

    assetManager.loadSoundFromFile("blockPlace.ogg", "BLOCK_PLACEMENT");
    assetManager.loadSoundFromFile("explosion.wav", "EXPLOSION");
    assetManager.loadSoundFromFile("save.ogg", "SAVE");
    assetManager.loadSoundFromFile("teleport.ogg", "TELEPORT");

    assetManager.loadFontFromFile("lucon.ttf", "LUCON");
    assetManager.loadFontFromFile("Akashi.ttf", "AKASHI");

    assetManager.loadTextureFromFile("characters.png", "CHARACTERS_SHEET_1");
    assetManager.loadTextureFromFile("rpgcharacters.png", "CHARACTERS_SHEET_2");
    assetManager.loadTextureFromFile("tntentity.png", "TNT");
    assetManager.loadTextureFromFile("hand.png", "HAND");
    assetManager.loadTextureFromFile("inventorySelected.png", "SELECTED_SLOT");
    assetManager.loadTextureFromFile("inventoryBar.png", "INVENTORY_BAR");
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
    currentWorld->updateChunks(dt);

    if (focused) { player->update(dt); }

	currentWorld->removeEntitiesThatNeedToBeRemoved();
	//Update the entities of the world

	for (unsigned int i = 0; i < currentWorld->getEntities().size(); i++)
		currentWorld->getEntities()[i]->update(dt);

	game->getWorldView().setCenter(cameraFollow->getPosition());

	//Update the GUI
	for (unsigned int i = 0; i < gui.size(); i++)
	{
		gui[i]->update(dt);
	}

}

void StateGame::draw(sf::RenderWindow &window) {
	//Set the right view for world drawing
	window.setView(game->getWorldView());

	//Get chunks to draw
	std::vector<Chunk> chunksToDraw;
	sf::Vector2i playerChunk(floor(player->getWorldPos().x / Chunk::CHUNK_SIZE), floor(player->getWorldPos().y / Chunk::CHUNK_SIZE));
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            chunksToDraw.push_back(currentWorld->pgetChunk(playerChunk + sf::Vector2i(i, j)));
        }
    }
	//Draw the ground
	for (unsigned int i = 0; i < chunksToDraw.size(); i++)
    {
        sf::VertexArray groundQuads(sf::Quads, 4 * Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE);
        for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
        {
            for (int y = 0; y < Chunk::CHUNK_SIZE; y++)
            {
                unsigned short groundId = chunksToDraw.at(i).getGround(sf::Vector2i(x, y));

                groundQuads[(x + y * Chunk::CHUNK_SIZE) * 4 + 0].position = sf::Vector2f(x + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE - 0.5f, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE - 0.5f);
                groundQuads[(x + y * Chunk::CHUNK_SIZE) * 4 + 1].position = sf::Vector2f(x + 0.5f + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE - 0.5f);
                groundQuads[(x + y * Chunk::CHUNK_SIZE) * 4 + 2].position = sf::Vector2f(x + 0.5f + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE, y + 0.5f + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);
                groundQuads[(x + y * Chunk::CHUNK_SIZE) * 4 + 3].position = sf::Vector2f(x + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE - 0.5f, y + 0.5f + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);

                sf::IntRect rect = tileset.getGroundRect(groundId);
                groundQuads[(x + y * Chunk::CHUNK_SIZE) * 4 + 0].texCoords = sf::Vector2f(rect.left, rect.top);
                groundQuads[(x + y * Chunk::CHUNK_SIZE) * 4 + 1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
                groundQuads[(x + y * Chunk::CHUNK_SIZE) * 4 + 2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
                groundQuads[(x + y * Chunk::CHUNK_SIZE) * 4 + 3].texCoords = sf::Vector2f(rect.left, rect.top + rect.height);
            }
        }
        sf::Transform tr;
        tr.scale(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        sf::RenderStates states;
        states.transform = tr;
        states.texture = tileset.getTexture();
        window.draw(groundQuads, states);
    }
    //Draw the blocks on the ground
    worldDraw.setSize(sf::Vector2f(TILE_SIZE_FLOAT, TILE_SIZE_FLOAT));
    for (unsigned int i = 0; i < chunksToDraw.size(); i++)
    {
        for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
        {
            for (int y = 0; y < Chunk::CHUNK_SIZE; y++)
            {
                unsigned short blockId = chunksToDraw.at(i).getBlock(sf::Vector2i(x, y));
                if (!blockId)
                    continue;
                if (!tileset.getBlockById(blockId)->hasVolume())
                {
                    worldDraw.setTextureRect(tileset.getBlockRect(blockId));
                    worldDraw.setPosition(sf::Vector2f((chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE + x) * TILE_SIZE_FLOAT
                                                    , (chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE + y) * TILE_SIZE_FLOAT));
                    window.draw(worldDraw);
                }
            }
        }
    }
	//Draw the blocks front side
	for (unsigned int i = 0; i < chunksToDraw.size(); i++)
    {
        sf::VertexArray blockQuads(sf::Quads, 0);
        for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
        {
            for (int y = 0; y < Chunk::CHUNK_SIZE; y++)
            {
                unsigned short blockId = chunksToDraw.at(i).getBlock(sf::Vector2i(x, y));

                if (!tileset.getBlockById(blockId)->hasVolume() || !blockId)
                    continue;

                sf::Vertex thisBlockQuads[4];
                thisBlockQuads[0].position = sf::Vector2f(x + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE - 0.5f, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);
                thisBlockQuads[1].position = sf::Vector2f(x + 0.5f + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);
                thisBlockQuads[2].position = sf::Vector2f(x + 0.5f + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE, y + 0.5f + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);
                thisBlockQuads[3].position = sf::Vector2f(x + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE - 0.5f, y + 0.5f + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);

                sf::IntRect rect = tileset.getBlockSideRect(blockId);
                thisBlockQuads[0].texCoords = sf::Vector2f(rect.left, rect.top);
                thisBlockQuads[1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
                thisBlockQuads[2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
                thisBlockQuads[3].texCoords = sf::Vector2f(rect.left, rect.top + rect.height);

                for (int j = 0; j < 4; j++)
                {
                    thisBlockQuads[j].color = tileset.getSideTint(blockId);
                    blockQuads.append(thisBlockQuads[j]);
                }
            }
        }
        sf::Transform tr;
        tr.scale(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        sf::RenderStates states;
        states.transform = tr;
        states.texture = tileset.getTexture();
        window.draw(blockQuads, states);
    }

	//Draw all entities
	for (unsigned int i = 0; i < currentWorld->getEntities().size(); i++)
        window.draw(*(currentWorld->getEntities()[i]));
	//And draw the player
	window.draw(*player);

	//Draw the actual blocks
	for (unsigned int i = 0; i < chunksToDraw.size(); i++)
    {
        sf::VertexArray blockQuads(sf::Quads, 0);
        for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
        {
            for (int y = 0; y < Chunk::CHUNK_SIZE; y++)
            {
                unsigned short blockId = chunksToDraw.at(i).getBlock(sf::Vector2i(x, y));

                if (!tileset.getBlockById(blockId)->hasVolume() || !blockId)
                    continue;

                sf::Vertex thisBlockQuads[4];
                thisBlockQuads[0].position = sf::Vector2f(x + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE - 0.5f, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE - 1);
                thisBlockQuads[1].position = sf::Vector2f(x + 0.5f + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE - 1);
                thisBlockQuads[2].position = sf::Vector2f(x + 0.5f + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);
                thisBlockQuads[3].position = sf::Vector2f(x + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE - 0.5f, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);

                sf::IntRect rect = tileset.getBlockRect(blockId);
                thisBlockQuads[0].texCoords = sf::Vector2f(rect.left, rect.top);
                thisBlockQuads[1].texCoords = sf::Vector2f(rect.left + rect.width, rect.top);
                thisBlockQuads[2].texCoords = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
                thisBlockQuads[3].texCoords = sf::Vector2f(rect.left, rect.top + rect.height);

                for (int j = 0; j < 4; j++)
                    blockQuads.append(thisBlockQuads[j]);
            }
        }
        sf::Transform tr;
        tr.scale(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        sf::RenderStates states;
        states.transform = tr;
        states.texture = tileset.getTexture();
        window.draw(blockQuads, states);
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
	for (unsigned int i = 0; i < currentWorld->getEntities().size(); i++)
        (*currentWorld->getEntities()[i]).drawMore(window);
    player->drawMore(window);

	//Draw the map
	mapView.setCenter(game->getWorldView().getCenter());
	window.setView(mapView);
	//Same method
	for (unsigned int i = 0; i < chunksToDraw.size(); i++)
    {
        sf::VertexArray pixelQuads(sf::Quads, 0);
        for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
        {
            for (int y = 0; y < Chunk::CHUNK_SIZE; y++)
            {
                unsigned short blockId = chunksToDraw.at(i).getBlock(sf::Vector2i(x, y));
                unsigned short groundId = chunksToDraw.at(i).getGround(sf::Vector2i(x, y));

                sf::Vertex thisPixelQuads[4];
                thisPixelQuads[0].position = sf::Vector2f(x + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE - 0.5f, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE - 1);
                thisPixelQuads[1].position = sf::Vector2f(x + 0.5f + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE - 1);
                thisPixelQuads[2].position = sf::Vector2f(x + 0.5f + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);
                thisPixelQuads[3].position = sf::Vector2f(x + chunksToDraw.at(i).getPosition().x * Chunk::CHUNK_SIZE - 0.5f, y + chunksToDraw.at(i).getPosition().y * Chunk::CHUNK_SIZE);

                for (int j = 0; j < 4; j++)
                {
                    thisPixelQuads[j].color = tileset.getMapPixel(groundId, blockId);
                    pixelQuads.append(thisPixelQuads[j]);
                }
            }
        }
        sf::Transform tr;
        tr.scale(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        window.draw(pixelQuads, tr);
    }

	//Draw entities on map
	for (unsigned int i = 0; i < currentWorld->getEntities().size(); i++)
		window.draw(*(currentWorld->getEntities()[i]->getOnMap()));
	window.draw(*player->getOnMap());
	window.draw(mapFrame);

    //Draw the gui
	window.setView(game->getGuiView());

	for (unsigned int i = 0; i < gui.size(); i++)
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
    currentWorld->preDelete();
	delete currentWorld;

	//And load the new world
	currentWorld = &world;

	//Set the current world for the player
	player->setCurrentWorld(currentWorld);
}

StateGame::~StateGame() {
	//We delete the world to prevent memory leaks
	currentWorld->preDelete();
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

        default: break;
    }

}

void StateGame::onStop()
{
    if (onlineMode)
        nManager.disconnect();
}

sf::View& StateGame::getGuiView() { return game->getGuiView(); };


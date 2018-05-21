#pragma once

#include "SFML/Graphics.hpp"
#include "StateBase.h"
#include "../Game.h"
#include "../Worlds/World.h"
#include "../Utils/TileSet.h"
#include "../Entities/Player.h"
#include "../Utils/SoundManager.h"
#include "../Entities/Entities.h"
#include "../Gui/Gui.h"
#include "../Gui/InventoryGui.h"
#include <vector>
#include <memory>

class StateGame : public StateBase
{
public:
	StateGame(Game& g, bool online);

	void handleInput()					override;
	void update(float dt)				override;
	void draw(sf::RenderWindow &window) override;

	sf::View& getMapView();
	sf::View& getGuiView();
	void setWorld(World &world);

	TileSet* getTileset();

	Entities* cameraFollow;

	unsigned static const int TILE_SIZE = 100;
	const float TILE_SIZE_FLOAT = 100.0f;

	void setClicks();

	World* getWorld();

	SoundManager* getSoundManager();

	~StateGame();

    void handleEvent(sf::Event &event) override;

    inline bool isOnline() { return onlineMode; };

    unsigned int getEntityId();

private:

	std::vector<std::unique_ptr<Gui>> gui;
	InventoryGui *inventoryGui;

	World *currentWorld = nullptr;

	sf::View mapView;
	sf::RectangleShape mapFrame;
	sf::RectangleShape worldDraw;
	sf::RectangleShape mapDraw;
	sf::RectangleShape pointer;
	sf::RectangleShape mouse;

	bool leftClicking = false;
	bool rightClicking = false;

	unsigned short inventoryCursorId = 0;
	bool isPlaceKeyPressed = false;

	TileSet tileset;
	SoundManager soundManager;

	Player *player;

    bool onlineMode;

    unsigned int nextEntityId = 0;

};


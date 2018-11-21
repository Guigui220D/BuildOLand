#pragma once

#include "SFML/Graphics.hpp"
#include "StateBase.h"
#include "../Game.h"
#include "../Worlds/World.h"
#include "../Utils/TileSet.h"
#include "../Entities/Player.h"
#include "../Entities/Entities.h"

#include <vector>
#include <memory>
#include "../Utils/NetworkManager.h"

#include "../Gui/Gui.h"
#include "../Gui/InventoryGui.h"
#include "../Gui/ChatGui.h"
#include "../Gui/GuiShroud.h"
#include "../Gui/GuiButton.h"

class StateGame : public StateBase
{
public:
    static const int TILE_SIZE = 100;
	const float TILE_SIZE_FLOAT = 100.0f;

	StateGame(Game& game, bool online, std::string playerName = "Player", std::string adressInput = "");
	~StateGame() override;

	void initAssets() override;

	void handleInput()					override;
	void update(float dt, bool focused)	override;
	void draw(sf::RenderWindow &window) override;
	void onStop()                       override;

	inline sf::View& getMapView() { return mapView; };
	sf::View& getGuiView();
	void setWorld(World &world);

	Entities* cameraFollow;

	inline void setClicks() { leftClicking = rightClicking = true; };

	inline World* getWorld() { return currentWorld; };
	inline TileSet* getTileset() { return &tileset; };
	inline Player* getPlayer() { return player; };

    void handleEvent(sf::Event &event) override;

    inline bool isOnline() { return onlineMode; };
    inline bool isOnlineAndAvailible() { return onlineMode && nManager.isConnected(); };
    inline NetworkManager* getNetworkManager() { return &nManager; }


private:

    NetworkManager nManager;
    bool onlineMode;

	World *currentWorld = nullptr;

	sf::View mapView;
	sf::RectangleShape mapFrame;
	sf::RectangleShape worldDraw;
	sf::RectangleShape mapDraw;
	sf::RectangleShape pointer;
	sf::RectangleShape mouse;

	bool rightClicking = false;
	bool leftClicking = false;

	unsigned short inventoryCursorId = 0;
	bool isPlaceKeyPressed = false;

	TileSet tileset;

	Player *player;

    GuiDomain guiDomain;
    InventoryGui *inventoryGui;
	//ChatGui *chatGui;

	bool paused;
	GuiDomain pauseGuiDomain;
    GuiButton* pauseResumeButton;
    GuiButton* pauseSettingsButton;
    GuiButton* pauseExitButton;

    bool inSettings;
    GuiDomain settingsGuiDomain;

};


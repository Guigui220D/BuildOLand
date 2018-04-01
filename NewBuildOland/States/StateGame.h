#pragma once

#include "SFML/Graphics.hpp"
#include "StateBase.h"
#include "../Game.h"
#include "../Worlds/World.h"
#include "../Utils/TileSet.h"
#include "../Entities/Player.h"
#include "../Entities/Entities.h"
#include "../Utils/SoundManager.h"
#include <vector>

class StateGame : public StateBase
{
public:
	StateGame(Game& game);
	
	void handleInput()					override;
	void update(float dt)				override;
	void draw(sf::RenderWindow &window) override;
	
	sf::View& getMapView();

	void setWorld(World &world);

	TileSet* getTileset();

	Entities* cameraFollow;

	unsigned static const int TILE_SIZE = 100;
	const float TILE_SIZE_FLOAT = 100.0f;

	void setClicks();

	World* getWorld();

	SoundManager* getSoundManager();

	~StateGame();

	std::vector<Entities> entities;

private:
	World *currentWorld = nullptr;
	
	sf::View mapView;
	sf::RectangleShape mapFrame;
	sf::RectangleShape worldDraw;
	sf::RectangleShape mapDraw;
	sf::RectangleShape pointer;
	sf::RectangleShape mouse;

	bool leftClicking = false;
	bool rightClicking = false;
	
	unsigned short blockPlaceId = 1;
	bool isPlaceKeyPressed = false;

	TileSet tileset;
	SoundManager soundManager;

	Player player;

};


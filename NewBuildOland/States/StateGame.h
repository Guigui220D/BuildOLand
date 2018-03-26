#pragma once

#include "SFML/Graphics.hpp"
#include "StateBase.h"
#include "../Game.h"
#include "../Worlds/World.h"
#include "../Utils/TileSet.h"
#include "../Entities/Player.h"

class StateGame : public StateBase
{
public:
	StateGame(Game& game);
	
	void handleInput()					override;
	void update(float dt)				override;
	void draw(sf::RenderWindow &window) override;
	
	sf::View& getMapView();

	void setWorld(World &world);

	Entities* cameraFollow;

	unsigned static const int TILE_SIZE = 100;
	const float TILE_SIZE_FLOAT = 100.0f;

	World* getWorld();

	~StateGame();

private:
	World *currentWorld = nullptr;
	
	sf::View mapView;
	sf::RectangleShape mapFrame;
	sf::RectangleShape worldDraw;
	sf::RectangleShape mapDraw;
	sf::RectangleShape pointer;

	bool leftClicking = false;
	bool rightClicking = false;

	Player player;
};


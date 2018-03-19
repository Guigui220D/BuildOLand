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

	static unsigned int getTileSize();

	~StateGame();

private:
	World *currentWorld = nullptr;
	
	unsigned static const int TILE_SIZE = 100;
	TileSet tileset;
	sf::View mapView;
	sf::RectangleShape mapFrame;
	sf::RectangleShape worldDraw;
	sf::RectangleShape mapDraw;
	

	Player player;
};


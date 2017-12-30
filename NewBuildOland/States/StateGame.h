#pragma once

#include "SFML/Graphics.hpp"
#include "StateBase.h"
#include "../Game.h"
#include "../Worlds/World.h"
#include "../Utils/TileSet.h"

class StateGame : public StateBase
{
public:
	StateGame(Game& game);
	
	void handleInput()					override;
	void update(float dt)				override;
	void draw(sf::RenderWindow &window) override;

	sf::View& getMapView();

	void setWorld(World &world);

	~StateGame();

private:
	sf::CircleShape circle; //Temporary, used for testing
	World *currentWorld = nullptr;
	TileSet tileset;
	sf::View mapView;
	sf::RectangleShape mapFrame;
	sf::RectangleShape worldDraw;
	sf::RectangleShape mapDraw;
};


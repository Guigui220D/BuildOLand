#pragma once

#include "SFML/Graphics.hpp"

class Game;

class StateBase
{
public:
	StateBase(Game& game);

	virtual void handleInput() = 0;
	virtual void update(float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;

protected:
	Game* game = nullptr;
	
};


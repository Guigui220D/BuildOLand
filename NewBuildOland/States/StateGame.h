#pragma once

#include "SFML\Graphics.hpp"
#include "StateBase.h"
#include "../Game.h"

class StateGame : public StateBase
{
public:
	StateGame(Game& game);
	
	void handleInput()					override;
	void update(float dt)				override;
	void draw(sf::RenderWindow &window) override;

private:
	sf::CircleShape circle; //Temporary, used for testing
};


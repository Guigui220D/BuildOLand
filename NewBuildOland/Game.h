#pragma once

#include <SFML/Graphics.hpp>
#include "States/StateBase.h"
#include "States/StateGame.h"

class Game
{
public:
	Game();

	void run();

	sf::RenderWindow& getWindow();

	~Game();

private:
	sf::RenderWindow window;
	StateBase *currentState;
};

class Game
{
public:
	Game();
	~Game();
};


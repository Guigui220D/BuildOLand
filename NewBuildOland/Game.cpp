#include "stdafx.h"
#include "Game.h"


Game::Game()
	: window(sf::VideoMode(200, 200), "BuildOLand")
	, currentState(0)
{
	window.setFramerateLimit(30);

	//Setting the current state to a Game State
	currentState = new StateGame(*this);
}

void Game::run()
{
	//Start the game loop
	while (window.isOpen())
	{
		//First step, get the input from the player
		currentState->handleInput();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Then update everything in that state (positions etc..)
		//The argument is the time between the last frame (delta time)
		//todo: calculate the real delta time
		currentState->update(0.0);
		
		window.clear();
		//Finally draw everything on the window after the changes have been made
		currentState->draw(window);
		window.display();
	}
}

sf::RenderWindow& Game::getWindow() {
	return window;
}

Game::~Game()
{
	//We delete all the pointers to prevent memory leaks
	//(because we allocated it with "new")
	delete currentState;
}

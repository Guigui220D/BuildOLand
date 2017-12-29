#include "stdafx.h"
#include "Game.h"
#include <iostream>


Game::Game()
	: window(sf::VideoMode(800, 600), "BuildOLand")
	, currentState(0)
{
	window.setFramerateLimit(30);

	//Setting the current state to a Game State
	guiView = sf::View();
	//The worldView sizing is automated
	worldView = sf::View();
	worldView.setCenter(0, 0);
	guiView = sf::View();
	guiView.setSize(1, 1);
	guiView.setCenter(0.5f, 0.5f);
	updateView();

	currentState = new StateGame(*this);
}

void Game::run()
{
	//Start the game loop
	while (window.isOpen())
	{
		//First step, get the input from the player
		currentState->handleInput();

		//The event handler
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
				updateView();
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

void Game::updateView()
{
	//Redimention sans déformation
	if (window.getSize().x < MIN_SIZE)
		window.setSize(sf::Vector2u(MIN_SIZE, window.getSize().y));
	if (window.getSize().y < MIN_SIZE)
		window.setSize(sf::Vector2u(window.getSize().x, MIN_SIZE));
	if (window.getSize().y > window.getSize().x)
	{
		float ratio = (float)window.getSize().y / window.getSize().x;
		float ySize = ratio * 800;
		worldView.setSize(sf::Vector2f(800, ySize));
	}
	else
	{
		float ratio = (float)window.getSize().x / window.getSize().y;
		float xSize = ratio * 800;
		worldView.setSize(sf::Vector2f(xSize, 800));
	}
}

sf::RenderWindow& Game::getWindow() {
	return window;
}

sf::View& Game::getWorldView() {
	return worldView;
}

sf::View& Game::getGuiView() {
	return guiView;
}


Game::~Game()
{
	//We delete pointers to prevent memory leaks
	//(because we allocated it with "new")
	delete currentState;
}
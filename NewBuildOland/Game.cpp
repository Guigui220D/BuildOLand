#include "Game.h"
#include "States/StateMenu.h"
#include <iostream>

#include "GameGlobal.h"

Game::Game() :
	window(sf::VideoMode(800, 600), "BuildOLand"),
	currentState(0)
{
    initGlobalAssets();

	Image icon;
	icon.loadFromFile("Res/icon.png");
	window.setIcon(256, 256, icon.getPixelsPtr());

	//window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(30);

	//Setting the current state to a Game State
	//The worldView sizing is automated
	worldView = sf::View();
	worldView.setCenter(0, 0);

	guiView = sf::View();
	guiView.setCenter(0, 0);

	updateView();

	currentState = new StateMenu(*this);
}

void Game::initGlobalAssets()
{
    GameGlobal::assets.loadFontFromFile("lucon.ttf", "LUCON");

    GameGlobal::assets.loadTextureFromFile("newTileset.png", "TILESET");
    GameGlobal::assets.loadTextureFromFile("logo.png", "LOGO");
}

void Game::run()
{
	sf::Clock clk = Clock();
	sf::Clock fpsClk = Clock();
	int count = 0;
	focused = window.hasFocus();
	//Start the game loop
	while (window.isOpen())
	{
		//First step, get the input from the player
		if (window.hasFocus())
			currentState->handleInput();
		//The event handler
		sf::Event event;
		while (window.pollEvent(event))
		{
		    switch (event.type)
		    {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                updateView();
                break;
            case sf::Event::LostFocus:
                focused = false;
                break;
            case sf::Event::GainedFocus:
                focused = true;
                break;
            default:
                //Send the event to the current state
                currentState->handleEvent(event);
                break;
		    }

		}

		//Then update everything in that state (positions etc..)
		//The argument is the time between the last frame (delta time)
        currentState->update(clk.restart().asSeconds(), focused);

		window.clear();
		//Finally draw everything on the window after the changes have been made
		currentState->draw(window);
		window.display();
		count++;
		if (count >= 1000)
		{
			float time = fpsClk.restart().asSeconds();
			time /= count;
			float fps = 1 / time;
			std::cout << "FPS : " << fps << std::endl;
			count = 0;
			lastFps = fps;
		}
	}

	currentState->onStop();
}

void Game::updateView()
{
	//Resize without deformation
	if (window.getSize().x < MIN_SIZE)
		window.setSize(sf::Vector2u(MIN_SIZE, window.getSize().y));
	if (window.getSize().y < MIN_SIZE)
		window.setSize(sf::Vector2u(window.getSize().x, MIN_SIZE));
	if (window.getSize().y > window.getSize().x)
	{
		float ratio = (float)window.getSize().y / window.getSize().x;
		float ySize = ratio * 800;
		worldView.setSize(sf::Vector2f(800, ySize));
		guiView.setSize(sf::Vector2f(800, ySize));
	}
	else
	{
		float ratio = (float)window.getSize().x / window.getSize().y;
		float xSize = ratio * 800;
		worldView.setSize(sf::Vector2f(xSize, 800));
		guiView.setSize(sf::Vector2f(xSize, 800));
	}

}

sf::RenderWindow& Game::getWindow() {
	return window;
}

StateBase* Game::getCurrentState() {
	return currentState;
}

void Game::setCurrentState(StateBase *state) {
	delete currentState;

	currentState = state;
}

sf::View& Game::getWorldView() {
	return worldView;
}

sf::View& Game::getGuiView() {
	return guiView;
}

float Game::getFPS()
{
    return lastFps;
}

Game::~Game()
{
	//We delete pointers to prevent memory leaks
	//(because we allocated it with "new")
	delete currentState;
}

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
	StateBase* getCurrentState();
	void setCurrentState(StateBase* state);

	sf::View& getWorldView();
	sf::View& getGuiView();

	void updateView();
	const unsigned int MIN_SIZE = 200;

	~Game();

	float getFPS();

private:
	sf::RenderWindow window;
	StateBase *currentState;

	/*These view are in the game, because guiView is constant,
	and worldview is needed in almost all states
	Other views can be added by states if needed*/
	sf::View guiView;
	sf::View worldView;

	float lastFps;
	bool focused;
};

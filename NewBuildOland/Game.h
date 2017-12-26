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

	/*These view are in the game, because guiView is constant,
	and worldview is needed in almost all states
	Other view can be added by states if needed*/
	sf::View guiView;
	sf::View worldView;
	void updateView();
	const unsigned int MIN_SIZE = 200;

	~Game();

private:
	sf::RenderWindow window;
	StateBase *currentState;
};

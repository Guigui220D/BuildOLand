#pragma once
#include <SFML\Graphics.hpp>

class Gui : sf::RectangleShape
{
public:
	Gui(StateBase& state);
	~Gui();
	StateBase* state = nullptr;
	Game* game = nullptr;

};


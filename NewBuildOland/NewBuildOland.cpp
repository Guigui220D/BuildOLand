﻿// NewBuildOland.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	//Starts the game
	Game game;

	game.run();
	
	return 0;
}


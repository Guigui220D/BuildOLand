#include "stdafx.h"
#include "StateGame.h"
#include "../Worlds/FlatWorld.h"
#include <iostream>

StateGame::StateGame(Game& game)
	: StateBase(game),
	circle(100.0f)
{
	//Set the world
	currentWorld = new FlatWorld(game);

	circle.setFillColor(sf::Color::Red);
}

void StateGame::handleInput() {

}

void StateGame::update(float dt) {

}

void StateGame::draw(sf::RenderWindow &window) {
	window.setView(game->getWorldView());
	window.draw(circle);
}

void StateGame::setWorld(World &world) {
	//We delete the old world
	//as we will be changing the pointer's adress
	delete currentWorld;

	//And load the new world
	currentWorld = &world;
}

StateGame::~StateGame()
{
	//We delete pointers to prevent memory leaks
	delete currentWorld;
}
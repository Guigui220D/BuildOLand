#include "stdafx.h"
#include "StateGame.h"


StateGame::StateGame(Game& game)
	: StateBase(game),
	circle(100.0f)
{
	circle.setFillColor(sf::Color::Red);
}

void StateGame::handleInput() {

}

void StateGame::update(float dt) {

}

void StateGame::draw(sf::RenderWindow &window) {
	window.setView(game->worldView);
	window.draw(circle);
}
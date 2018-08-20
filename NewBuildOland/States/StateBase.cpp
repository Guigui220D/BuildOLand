#include "StateBase.h"


StateBase::StateBase(Game& game)
	: game(&game)
{

}

StateBase::~StateBase() { }

Game* StateBase::getGame()
{
    return game;
}

void StateBase::handleEvent(sf::Event &event) {

}

void StateBase::onStop()
{

}

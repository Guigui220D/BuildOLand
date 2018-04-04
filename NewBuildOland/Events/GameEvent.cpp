#include "GameEvent.h"
#include "../States/StateGame.h"

GameEvent::GameEvent(StateGame* state)
{
	game = state;
}


GameEvent::~GameEvent()
{
}

StateGame * GameEvent::getState()
{
	return game;
}

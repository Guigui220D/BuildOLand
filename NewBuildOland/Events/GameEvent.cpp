#include "stdafx.h"
#include "GameEvent.h"
#include "../States/StateBase.h"

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

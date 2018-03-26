#pragma once
#include "../States/StateGame.h"

class GameEvent
{
public:
	GameEvent(StateGame* state);
	~GameEvent();
	StateGame* getState();
protected:
	StateGame * game;
};


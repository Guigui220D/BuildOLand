#pragma once
#include "../States/StateGame.h"

class GameEvent
{
public:
	GameEvent(StateGame* state);
	~GameEvent();
	inline StateGame* getState() { return game; };
protected:
	StateGame* game;
};


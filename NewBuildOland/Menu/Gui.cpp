#include "stdafx.h"
#include "Gui.h"
#include "../States/StateBase.h"
#include "../Game.h"


Gui::Gui(StateBase& parent) : state(&parent)
{
	game = state->game;	
}


Gui::~Gui()
{
	
}

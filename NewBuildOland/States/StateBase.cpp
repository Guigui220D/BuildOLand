#include "stdafx.h"
#include "StateBase.h"


StateBase::StateBase(Game& game) 
	: game(&game)
{
	
}

TileSet* StateBase::getTileset() {
	return &tileset;
}
#include "StateBase.h"


StateBase::StateBase(Game& game)
	: game(&game)
{

}

Game* StateBase::getGame()
{
    return game;
}

void StateBase::resizedEvent() {

}

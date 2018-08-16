#include "MazeWorld.h"
#include "../States/StateGame.h"
#include "../Entities/BlackWarrior.h"
#include "../Entities/TNTEntity.h"

MazeWorld::MazeWorld(StateGame& stateGame)
	: World(stateGame, "mazeworld")
{

	{
	    BlackWarrior* blackWarrior = new BlackWarrior(this, getNextEntityId());
	    blackWarrior->init(4, 4);
        entities.push_back(blackWarrior);
	}

}


MazeWorld::~MazeWorld()
{
}

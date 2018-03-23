#include "stdafx.h"
#include <iostream>
#include "Events.h"

Events::Events()
{
}


Events::~Events()
{
}

void Events::OnBlockBreak(BlockBreakEvent e)
{
	std::cout << "Event : Block " << e.getOldBlock() << " broken at " << e.getPosition().x << ", " << e.getPosition().y << std::endl;
}

void Events::OnBlockBuild(BlockBuildEvent e)
{
	std::cout << "Event : Block " << e.getBlock() << " built at " << e.getPosition().x << ", " << e.getPosition().y << std::endl;
}

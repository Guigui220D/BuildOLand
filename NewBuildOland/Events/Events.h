#pragma once
#include <iostream>
#include "BlockBreakEvent.h"
#include "BlockBuildEvent.h"

class TileSet;

class Events
{
public:
	Events();
	~Events();
	static void OnBlockBreak(BlockBreakEvent e);
	static void OnBlockBuild(BlockBuildEvent e);

	static TileSet* tileset;

private:
};


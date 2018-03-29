#pragma once
#include <iostream>
#include "BlockBreakEvent.h"
#include "BlockBuildEvent.h"
#include "WalkOnEvent.h"
#include "BlockLeaveEvent.h"

class TileSet;

class Events
{
public:
	Events();
	~Events();
	static void OnBlockBreak(BlockBreakEvent e);
	static void OnBlockBuild(BlockBuildEvent e);
	static void OnWalkOnBlock(WalkOnEvent e);
	static void OnLeaveBlock(BlockLeaveEvent e);

	static TileSet* tileset;

private:
};


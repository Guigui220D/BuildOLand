#pragma once
#include <iostream>
#include "BlockBreakEvent.h"
#include "BlockBuildEvent.h"
#include "PlaceableEnterEvent.h"
#include "PlaceableLeaveEvent.h"

class TileSet;

class Events
{
public:
	Events();
	~Events();
	static void OnBlockBreak(BlockBreakEvent e);
	static void OnBlockBuild(BlockBuildEvent e);
	static void OnPlaceableEnter(PlaceableEnterEvent e);
	static void OnPlaceableLeave(PlaceableLeaveEvent e);

	static TileSet* tileset;

private:
};


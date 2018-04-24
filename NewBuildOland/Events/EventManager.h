#pragma once
#include <iostream>
#include "BlockBreakEvent.h"
#include "BlockBuildEvent.h"
#include "PlaceableEnterEvent.h"
#include "PlaceableLeaveEvent.h"
#include "GroundPlaceEvent.h"

class TileSet;

class EventManager
{
public:
	EventManager();
	~EventManager();
	static void OnBlockBreak(BlockBreakEvent e);
	static void OnBlockBuild(BlockBuildEvent e);
	static void OnGroundPlace(GroundPlaceEvent e);
	static void OnPlaceableEnter(PlaceableEnterEvent e);
	static void OnPlaceableLeave(PlaceableLeaveEvent e);

	static TileSet* tileset;
private:
};


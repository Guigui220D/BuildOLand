#pragma once
#include <iostream>
#include "BlockBreakEvent.h"
#include "BlockBuildEvent.h"
#include "PlaceableEnterEvent.h"
#include "PlaceableLeaveEvent.h"
#include "GroundPlaceEvent.h"
#include "BlockInteractEvent.h"

class TileSet;
class StateGame;

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
	static void OnBlockInteract(BlockInteractEvent e);

	static TileSet* tileset;
	static StateGame* state;
private:
};


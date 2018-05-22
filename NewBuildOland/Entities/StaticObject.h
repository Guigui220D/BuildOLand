#pragma once
#include "Entities.h"

class StaticObject : public Entities
{
public:
	StaticObject(World *world, unsigned id);
	~StaticObject();
};


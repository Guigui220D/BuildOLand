#pragma once
#include "Chunk.h"
#include <vector>

class Entities;

struct CachedChunk
{
    Chunk chunk;
    std::vector<Entities*> entities;
};


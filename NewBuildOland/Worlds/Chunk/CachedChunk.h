#pragma once
#include "Chunk.h"
#include <vector>

class Entities;

struct CachedChunk
{
    std::vector<unsigned char> getData();
    Chunk chunk;
    std::vector<Entities*> entities;
};


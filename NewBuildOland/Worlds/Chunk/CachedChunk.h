#pragma once
#include "Chunk.h"
#include <queue>
#include <memory>

class Entities;

struct CachedChunk
{
    std::vector<unsigned char> getData();
    std::shared_ptr<Chunk> chunk;
    std::vector<Entities*> entities;
};


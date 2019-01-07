#pragma once
#include "Block.h"
#include "../Events/EventManager.h"

class TNTBlock : public Block
{
    public:
        TNTBlock(sf::IntRect textureRect, sf::IntRect faceRect);
        ~TNTBlock();
        virtual void onBlockInteract(BlockInteractEvent e) override;
};

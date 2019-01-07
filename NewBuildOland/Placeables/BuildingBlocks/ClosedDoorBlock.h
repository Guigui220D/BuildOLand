#pragma once

#include "../Block.h"
#include "../Events/EventManager.h"

class ClosedDoorBlock : public Block
{
    public:
        ClosedDoorBlock(sf::IntRect textureRect, sf::IntRect faceRect);
        virtual ~ClosedDoorBlock();
        virtual void onBlockInteract(BlockInteractEvent e) override;
    protected:

    private:
};


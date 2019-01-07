#pragma once

#include "../Block.h"
#include "../Events/EventManager.h"

class OpenDoorBlock : public Block
{
    public:
        OpenDoorBlock(sf::IntRect textureRect, sf::IntRect faceRect);
        virtual ~OpenDoorBlock();
        virtual void onBlockInteract(BlockInteractEvent e) override;
    protected:

    private:
};

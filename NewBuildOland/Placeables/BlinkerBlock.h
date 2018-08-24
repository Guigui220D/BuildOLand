#pragma once
#pragma once
#include "Block.h"
#include "../Events/EventManager.h"

class BlinkerBlock : public Block
{
    public:
        BlinkerBlock(sf::IntRect textureRect, sf::IntRect faceRect);
        virtual ~BlinkerBlock();

        virtual inline TileEntityCodes getTileEntity() { return TileEntityCodes::blinker; }

    protected:

    private:
};

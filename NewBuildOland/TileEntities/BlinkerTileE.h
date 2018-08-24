#pragma once
#include "TileEntities.h"

class BlinkerTileE : public TileEntities
{
    public:
        BlinkerTileE(World* world, sf::Vector2i blockPos);
        virtual ~BlinkerTileE();

        void update(float delta) override;
        void draw(sf::RenderWindow& window) override;

    protected:

    private:

        bool block = true;
};

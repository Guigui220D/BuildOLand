#pragma once
#include "Entities.h"

class TNTEntity : public Entities
{
    public:
        TNTEntity(World* world, unsigned id, sf::Vector2i pos);
        ~TNTEntity();

        inline EntityCodes getCode() const override { return EntityCodes::tnt; };

        void update(float delta) override;

        void explode(sf::Vector2i center);

        void takePacket(sf::Packet p) override;

    private:
        sf::Clock fuse;
        sf::Vector2i worldPos;

        float fuseLenght;
};



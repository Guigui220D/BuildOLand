#pragma once
#include "Entities.h"

class TNTEntity : public Entities
{
    public:
        TNTEntity(World* world, unsigned id, sf::Vector2i pos);
        virtual ~TNTEntity();
        void update(float delta) override;

        void explode(sf::Vector2i center);

        virtual TNTEntity* clone() const { return new TNTEntity(*this); };

        std::vector<unsigned char> getBytes() override;

        virtual void takePacket(sf::Packet p) override;


    private:
        sf::Clock fuse;
        sf::Vector2i worldPos;
};



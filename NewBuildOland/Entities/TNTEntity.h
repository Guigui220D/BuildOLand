#pragma once
#include "Entities.h"

class TNTEntity : public Entities
{
    public:
        TNTEntity(World* world, unsigned id, sf::Vector2i pos);
        virtual ~TNTEntity();
        void update(float delta) override;

        virtual TNTEntity* clone() const { return new TNTEntity(*this); };

        std::vector<unsigned char> getBytes() override;

    private:
        sf::Clock fuse;
        sf::Vector2i worldPos;
};



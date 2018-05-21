#pragma once
#include "Entities.h"

class TNTEntity : public Entities
{
    public:
        TNTEntity(World* world, sf::Vector2u pos);
        virtual ~TNTEntity();
        void update(double delta) override;

    private:
        sf::Clock fuse;
        sf::Texture texture;
        sf::Vector2u worldPos;
};



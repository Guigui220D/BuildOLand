#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class World;

class TileEntities
{
    public:
        TileEntities(World* world, sf::Vector2i blockPos);
        virtual ~TileEntities();

        virtual void update(float delta) = 0;
        virtual void draw(sf::RenderWindow& window) = 0;

        inline World* getWorld() { return world; };
        sf::Vector2i getPosition() { return pos; };

    protected:

    private:
        World* world;
        sf::Vector2i pos;
};

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
        inline sf::Vector2i getPosition() { return pos; };

        virtual void takeData(std::vector<unsigned char> data) = 0;
        virtual std::vector<unsigned char> getData() = 0;

    protected:

    private:
        World* world;
        sf::Vector2i pos;
};

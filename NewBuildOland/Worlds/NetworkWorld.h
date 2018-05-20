#pragma once
#include "World.h"
#include "SFML/Network.hpp"

class NetworkWorld : public World
{
    public:
        NetworkWorld(StateGame& stateGame);
        virtual ~NetworkWorld();

        void generateWorld() override;

        bool loadWorld() override;
        bool saveWorld() override;

    protected:

    private:
};


#pragma once
#include "World.h"
#include "SFML/Network.hpp"
#include "../Utils/NetworkManager.h"
#include "../States/StateGame.h"

class NetworkWorld : public World
{
    public:
        NetworkWorld(StateGame& stateGame);
        virtual ~NetworkWorld();

        void generateWorld(sf::Packet p = sf::Packet()) override;

        bool loadWorld() override;
        bool saveWorld() override;

        inline NetworkManager* getNetworkManager() { return stateGame->getNetworkManager(); };

    protected:

    private:
};


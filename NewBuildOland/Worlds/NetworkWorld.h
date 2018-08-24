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
        void preDelete() override;

        void handlePacket(sf::Packet p) override;

        inline NetworkManager* getNetworkManager() { return stateGame->getNetworkManager(); };

        void loadChunk(sf::Vector2i chunk) override;
        void unloadChunk(sf::Vector2i chunk, bool erase) override;
        void flushChunkCache() override;
        void updateChunks(float delta) override;

    private:
        sf::Clock clk;
};


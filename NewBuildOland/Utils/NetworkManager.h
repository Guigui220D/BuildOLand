#pragma once
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include <iostream>
#include "PacketCodes.h"

class StateGame;

class NetworkManager
{
    public:
        static const unsigned short PORT = 54321;

        NetworkManager(StateGame* stategame);

        bool connect(char nick[16]);
        bool disconnect();
        inline bool isConnected() { return connected; };
        //All send functions
        inline bool askForWorld()
        {
            return oneCodeSend(MainCodes::requestWorld);
        };
        bool sendBlockBuild(sf::Vector2u pos, unsigned short block);
        bool sendBlockBreak(sf::Vector2u pos);
        bool sendGroundChange(sf::Vector2u, unsigned short ground);
        //Receive functions
        inline sf::Packet syncReceive()
        {
            std::cout << "Received something\n";
            sf::Packet p;
            server.receive(p);
            return p;
        };

    private:
        sf::TcpSocket server;
        bool connected = false;
        bool oneCodeSend(int code);
        inline bool sendPacket(sf::Packet p)
        {
            try { server.send(p); }
            catch (std::exception e)
            {
                return false;
            }
            return true;
        }

        sf::Thread receiveThread;   //Functions to receive data
        void receive();

        StateGame* game;


};

#pragma once
#include "SFML/Network.hpp"
#include "SFML/System.hpp"


class NetworkManager
{
    public:
        static const unsigned short PORT = 54321;
        //All message codes
        static const int WORLD_REQUEST = 1;

        static bool connect();
        static bool disconnect();
        static inline bool isConnected() { return connected; };
        //All send functions
        static inline bool askForWorld()
        {
            oneCodeSend(WORLD_REQUEST);
        };
        //All synced (not asnychronous) receive functions
        static inline sf::Packet recieve()
        {
            sf::Packet p;
            server.receive(p);
            return p;
        };
    private:
        static sf::TcpSocket server;
        static bool connected;
        static bool oneCodeSend(int code);
};

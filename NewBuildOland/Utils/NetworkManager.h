#pragma once
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include <iostream>

class NetworkManager
{
    public:
        static const unsigned short PORT = 54321;

        bool connect(char nick[16]);
        bool disconnect();
        inline bool isConnected() { return connected; };
        //All send functions
        inline bool askForWorld()
        {
            return oneCodeSend(REQUEST_WORLD);
        };
        bool sendBlockBuild(sf::Vector2u pos, unsigned short block);
        bool sendBlockBreak(sf::Vector2u pos);
        bool sendGroundChange(sf::Vector2u, unsigned short ground);
        //All synced (not asnychronous) receive functions
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

        //All message codes
        static const int DISCONNECT = 0;
        static const int REQUEST_CONNECTION = 1;
        static const int REQUEST_WORLD = 2;

        static const int CONNECT_REFUSED = 0;
        static const int CONNECT_ACCEPT = 1;

        //Connection refused codes
        static const int REASON_NULL = 0;
        static const int REASON_SERVER_NOT_READY = 1;
        static const int REASON_SERVER_FULL = 2;
        static const int REASON_NICK_ALREADY_TAKEN = 3;
        static const int REASON_INVALID_NICK = 4;
        static const int REASON_BANNED = 5;
        static const int REASON_ALREADY_CONNECTED = 6;

};

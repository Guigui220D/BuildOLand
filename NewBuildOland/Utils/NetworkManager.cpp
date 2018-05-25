#include "NetworkManager.h"
#include <iostream>
#include <string>

bool NetworkManager::connect(char nick[16])
{
    if (connected)
        return false;
    //Connect
    try
    {
        server.connect("localhost", PORT) == sf::Socket::Done;
    }
    catch (std::exception e)
    {
        std::cout << "Failed to connect" << std::endl;
        return false;
    }
    std::cout << "Connected to the server" << std::endl;
    //Request a connection with the nickname
    {
        sf::Packet p;
        p << REQUEST_CONNECTION << nick;
        try
        {
            server.send(p);
        }
        catch (std::exception e)
        {
            std::cout << "Failed to send a connection request" << std::endl;
            return false;
        }
    }
    std::cout << "Sent a connection request" << std::endl;
    //Get the answer
    {
        sf::Packet p = syncReceive();
        bool response = false;
        p >> response;
        //If accepted, response = 1, else 0
        if (!response)
        {
            int reason = 0;
            p >> reason;
            switch (reason)
            {
            case REASON_NULL:
                std::cout << "Connection refused, no reason" << std::endl;
                break;
            case REASON_SERVER_NOT_READY:
                std::cout << "Connection refused, server not ready" << std::endl;
                break;
            case REASON_SERVER_FULL:
                std::cout << "Connection refused, server is full" << std::endl;
                break;
            case REASON_NICK_ALREADY_TAKEN:
                std::cout << "Connection refused, this nick is already taken" << std::endl;
                break;
            case REASON_BANNED:
                std::cout << "Connection refused, you are banned" << std::endl;
                break;
            default:
                std::cout << "Connection refused, no reason" << std::endl;
                break;
            }
            return false;
        }
    }
    connected = true;
    return true;
}

bool NetworkManager::disconnect()
{
    if (!connected)
        return false;
    //TODO: Try to send a disconnect message
    oneCodeSend(DISCONNECT);
    server.disconnect();
    connected = false;
}

bool NetworkManager::oneCodeSend(int code)
{
    if (!connected)
        return false;
    sf::Packet p;
    p << code;
    try { server.send(p); }
    catch (std::exception e)
    {
        return false;
    }
    return true;
}




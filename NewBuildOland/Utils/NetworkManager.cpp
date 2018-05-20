#include "NetworkManager.h"
#include <iostream>

sf::TcpSocket NetworkManager::server;
bool NetworkManager::connected = false;

bool NetworkManager::connect()
{
    if (connected)
        return false;
    try
    {
        connected = server.connect("localhost", PORT) == sf::Socket::Done ? true : false;
    }
    catch (std::exception e)
    {
        connected = false;
    }
    if (!connected)
        std::cout << "Failed to connect" << std::endl;
    //TODO: Send a connect request
    return connected;
}

bool NetworkManager::disconnect()
{
    if (!connected)
        return false;
    //TODO: Try to send a disconnect message
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



#include "NetworkManager.h"
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
        p << MainCodes::requestConnection << nick;
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
        bool response = true;
        p >> response;
        //If accepted, response = 1, else 0
        if (!response)
        {
            int reason = 0;
            p >> reason;
            switch (reason)
            {
            case RefuseCodes::null:
                std::cout << "Connection refused, no reason" << std::endl;
                break;
            case RefuseCodes::serverNotReady:
                std::cout << "Connection refused, server not ready" << std::endl;
                break;
            case RefuseCodes::serverFull:
                std::cout << "Connection refused, server is full" << std::endl;
                break;
            case RefuseCodes::nickAlreadyTaken:
                std::cout << "Connection refused, this nick is already taken" << std::endl;
                break;
            case RefuseCodes::invalidNick:
                std::cout << "Connection refused, wrong nick" << std::endl;
                break;
            case RefuseCodes::banned:
                std::cout << "Connection refused, you are banned" << std::endl;
                break;
            case RefuseCodes::alreadyConnected:
                std::cout << "Connection refused, already connected ???" << std::endl;
                break;
            default:
                std::cout << "Connection refused, unknowns reason" << std::endl;
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
    oneCodeSend(MainCodes::disconnect);
    server.disconnect();
    connected = false;
}

bool NetworkManager::oneCodeSend(int code)
{
    if (!connected)
        return false;
    sf::Packet p;
    p << code;
    return sendPacket(p);
}

bool NetworkManager::sendBlockBreak(sf::Vector2u pos)
{
    sf::Packet p;
    p << MainCodes::edition; //Edition code
    p << EditionCodes::blockBreak; //Block break code
    p << pos.x;
    p << pos.y;
    return sendPacket(p);
}

bool NetworkManager::sendBlockBuild(sf::Vector2u pos, unsigned short block)
{
    sf::Packet p;
    p << MainCodes::edition; //Edition code
    p << EditionCodes::blockBuild; //Block build code
    p << pos.x;
    p << pos.y;
    p << block;
    return sendPacket(p);
}

bool NetworkManager::sendGroundChange(sf::Vector2u pos, unsigned short ground)
{
    sf::Packet p;
    p << MainCodes::edition; //Edition code
    p << EditionCodes::groundChange; //Ground place code
    p << pos.x;
    p << pos.y;
    p << ground;
    return sendPacket(p);
}




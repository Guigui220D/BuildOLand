#include "NetworkManager.h"
#include <string>
#include "../States/StateGame.h"
#include "../Entities/OtherPlayer.h"


NetworkManager::NetworkManager(StateGame* stategame)
    : receiveThread(&receive, this)
{
    game = stategame;
}

bool NetworkManager::connect(char nick[16], sf::IpAddress address, unsigned short port)
{
    server = address; //Temporary

    if (connected)
        return false;
    //Connect
    if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
    {
        std::cout << "Failed to connect" << std::endl;
        return false;
    }
    std::cout << "Bound to port : " << socket.getLocalPort() << std::endl;
    //Request a connection with the nickname
    {
        sf::Packet p;
        p << MainCodes::requestConnection << nick;
        if (socket.send(p, server, PORT) != sf::Socket::Done)
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
        p >> playerID;
    }
    connected = true;
    receiveThread.launch();
    return true;
}

bool NetworkManager::disconnect()
{
    if (!connected)
        return false;
    receiveThread.terminate();
    oneCodeSend(MainCodes::disconnect);
    connected = false;
    std::cout << "Disconnected\n";
    return true;
}

void NetworkManager::receive()
{
    //This is where we handle all incoming packets
    std::cout << "Started receive thread\n";
    while (1)
    {
        sf::Packet rec;
        sf::IpAddress sender;
        unsigned short port;
        if (socket.receive(rec, sender, port) == sf::Socket::Done)
        {
            int code;
            rec >> code;
            switch (code)
            {
            case MainCodes::edition:
                {
                    int editionCode = 0;
                    rec >> editionCode;
                    unsigned int x = 0, y = 0;
                    unsigned short id = 0;
                    rec >> x >> y >> id;
                    switch (editionCode)
                    {
                    case EditionCodes::setBlock:
                        game->getWorld()->setBlockId(sf::Vector2u(x, y), id);
                        break;

                    case EditionCodes::setGround:
                        game->getWorld()->setGroundId(sf::Vector2u(x, y), id);
                        break;
                    }
                }
                break;

            case MainCodes::sendWorld:
                {
                    game->getWorld()->generateWorld(rec);
                }
                break;

            case MainCodes::addEntity:
                {
                    unsigned int id;
                    rec >> id;
                    char nick[16];
                    rec >> nick;
                    if (id != playerID)
                    {
                        OtherPlayer* oplayer = new OtherPlayer(game->getWorld(), nick, id);
                        oplayer->init(0, 0);
                        game->getWorld()->addEntity(oplayer);
                    }
                }
                break;

            case MainCodes::removeEntity:
                {
                    unsigned int id;
                    rec >> id;
                    if (id != playerID)
                    {
                        Entities* ent = game->getWorld()->getEntityById(id);
                        if (ent == nullptr)
                        {
                           std::cout << "Entity with id " << id << " must be removed but doesn't exist.\n";
                           break;
                        }
                        ent->mustBeRemoved = true;
                    }
                }
                break;
            case MainCodes::entityAction:
                {
                    unsigned int id;
                    rec >> id;
                    if (id != playerID)
                    {
                        Entities* ent = game->getWorld()->getEntityById(id);
                        if (ent == nullptr)
                        {
                           std::cout << "Entity with id " << id << " must move but doesn't exist.\n";
                           break;
                        }
                        ent->takePacket(rec);
                    }
                }
                break;

            }
        }
    }
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




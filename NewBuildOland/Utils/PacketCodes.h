#pragma once
//This file should be the same in the game and in the server

enum MainCodes
{
    //Client -> Server
    disconnect = 0,
    requestConnection = 1,
    requestWorld = 2,
    playerMovement = 8,
    blockInteract = 9,
    //Both directions
    edition = 3,             //Break block, build block or change ground
    ping = -1,
    pong = -2,
    //Server -> Client
    sendWorld = 4,
    addEntity = 5,
    removeEntity = 6,
    entityAction = 7,
    kick = 10,
    notConnected = 11
};

enum RefuseCodes
{
    //Server -> Client
    noReasonRefuse = 0,
    serverNotReady = 1,
    serverFull = 2,
    nickAlreadyTaken = 3,
    invalidNick = 4,
    bannedRefuse = 5,
    alreadyConnected = 6
};

enum KickCodes
{
    noReasonKick = 0,
    bannedKick = 1,
    serverClosing = 2,
    serverRebooting = 3,
    technicalReason = 4,
    inactivity = 5
};

enum EditionCodes
{
    //Client->Server
    blockBreak = 0,
    blockBuild = 1,
    groundChange = 2,
    //Server ->Client
    setBlock = 3,
    setGround = 4
};

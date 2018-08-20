#pragma once
//This file should be the same in the game and in the server

enum MainCodes
{
    //Client -> Server
    disconnect = 0,
    requestConnection = 1,
    requestChunk = 2,
    playerMovement = 3,
    blockInteract = 4,
    //Both directions
    edition = 5,             //Break block, build block or change ground
    ping = -1,
    pong = -2,
    //Server -> Client
    kick = 6,
    notConnected = 7,
    sendChunk = 8,
    addEntity = 9,
    removeEntity = 10,
    entityAction = 11,
    tpPlayer = 12
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

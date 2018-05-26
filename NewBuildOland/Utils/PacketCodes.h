#pragma once

enum MainCodes
{
    disconnect = 0,
    requestConnection = 1,
    requestWorld = 2,
    edition = 3
};

enum RefuseCodes
{
    null = 0,
    serverNotReady = 1,
    serverFull = 2,
    nickAlreadyTaken = 3,
    invalidNick = 4,
    banned = 5,
    alreadyConnected = 6
};

enum EditionCodes
{
    blockBreak = 0,
    blockBuild = 1,
    groundChange = 2
};

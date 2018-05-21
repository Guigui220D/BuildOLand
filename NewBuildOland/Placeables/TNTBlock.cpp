#include "TNTBlock.h"
#include <iostream>

TNTBlock::TNTBlock(sf::IntRect textureRect, sf::IntRect faceRect) : Block(textureRect, "TNT", sf::Color(255, 100, 100), true, true, faceRect)
{
    //ctor
}

TNTBlock::~TNTBlock()
{
    //dtor
}

void TNTBlock::OnBlockBreak(BlockBreakEvent e)
{
    sf::Vector2u pos = e.getPosition();
    //Explosion
    sf::Sound* boomSound = e.getState()->getSoundManager()->getSound("explosion.wav");
	boomSound->setVolume(20);
	boomSound->play();
    for (int x = -2; x <= 2; x++)
    {
        for (int y = -2; y <= 2; y++)
        {
            if ((int)pos.x + x >= 0 && (int)pos.y + y >= 0)
            {
                if (x * x + y * y <= 6)
                {
                    unsigned short id = e.getState()->getWorld()->getBlockId(pos + sf::Vector2u(x, y));
                    e.getState()->getWorld()->setBlockId(pos + sf::Vector2u(x, y), 0);
                    EventManager::OnBlockBreak(BlockBreakEvent(pos + sf::Vector2u(x, y), id, nullptr, e.getState()));
                }
                if (x * x + y * y <= 4)
                    e.getState()->getWorld()->setGroundId(pos + sf::Vector2u(x, y), 4);
            }
        }
    }
}

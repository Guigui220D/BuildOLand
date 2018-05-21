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
            if (pos.x + x >= 0 && pos.y +y >= 0)
            {
                if (x * x + y * y <= 6)
                {
                    unsigned short oldBlockId = e.getState()->getWorld()->getBlockId(pos + sf::Vector2u(x, y));
                    e.getState()->getWorld()->setBlockId(pos + sf::Vector2u(x, y), 0);
                    EventManager::OnBlockBreak(BlockBreakEvent(pos + sf::Vector2u(x, y), oldBlockId, nullptr, e.getState()));
                }
                if (x * x + y * y <= 4) {
                    unsigned short oldGroundId = e.getState()->getWorld()->getGroundId(pos + sf::Vector2u(x, y));
                    e.getState()->getWorld()->setGroundId(pos + sf::Vector2u(x, y), 4);
                    EventManager::OnGroundPlace(GroundPlaceEvent(pos + sf::Vector2u(x, y), oldGroundId, 4, nullptr, e.getState()));
                }
            }
        }
    }
}

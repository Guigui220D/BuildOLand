#include "TNTEntity.h"
#include "../Events/EventManager.h"

TNTEntity::TNTEntity(World* world, sf::Vector2u pos)
    : Entities(world)
{
    worldPos = pos;
    fuse.restart();
    setSize(sf::Vector2f(100, 100));
    texture.loadFromFile("Res/tntentity.png");
    setTexture(&texture);
    setPosition(sf::Vector2f(pos.x * StateGame::TILE_SIZE, pos.y * StateGame::TILE_SIZE));
    setOrigin(sf::Vector2f(50, 50));
}

TNTEntity::~TNTEntity()
{
    //dtor
}

void TNTEntity::update(double delta)
{
    if (!mustBeRemoved && fuse.getElapsedTime().asSeconds() >= 2.0f)
    {
        sf::Sound* boomSound = currentWorld->getStateGame()->getSoundManager()->getSound("explosion.wav");
        boomSound->setVolume(20);
        boomSound->play();
        int xpos = worldPos.x;
        int ypos = worldPos.y;
        for (int x = -2; x <= 2; x++)
        {
            for (int y = -2; y <= 2; y++)
            {
                if ((int)xpos + x >= 0 && (int)ypos + y >= 0)
                {
                    if (x * x + y * y <= 6)
                    {
                        unsigned short oldBlockId = currentWorld->getBlockId(sf::Vector2u(xpos + x, ypos + y));
                        currentWorld->setBlockId(sf::Vector2u(xpos + x, ypos + y), 0);
                        EventManager::OnBlockBreak(BlockBreakEvent(sf::Vector2u(xpos + x, ypos + y), oldBlockId, nullptr, currentWorld->getStateGame()));
                    }
                    if (x * x + y * y <= 4) {
                        unsigned short oldGroundId = currentWorld->getGroundId(sf::Vector2u(xpos + x, ypos + y));
                        currentWorld->setGroundId(sf::Vector2u(xpos + x, ypos + y), 4);
                        EventManager::OnGroundPlace(GroundPlaceEvent(sf::Vector2u(xpos + x, ypos + y), oldGroundId, 4, nullptr, currentWorld->getStateGame()));
                    }
                }
            }
        }
        mustBeRemoved = true;
    }
}

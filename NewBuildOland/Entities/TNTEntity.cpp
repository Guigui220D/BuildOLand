#include "TNTEntity.h"
#include "../Events/EventManager.h"

TNTEntity::TNTEntity(World* world, unsigned id, sf::Vector2u pos)
    : Entities(world, id)
{
    worldPos = pos;
    fuse.restart();
    setSize(sf::Vector2f(80, 120));
    texture.loadFromFile("Res/tntentity.png");
    setTexture(&texture);
    setPosition(sf::Vector2f(pos.x * StateGame::TILE_SIZE, pos.y * StateGame::TILE_SIZE));
    setOrigin(sf::Vector2f(40, 80));
    setOnMapColor(sf::Color::Red);
}

TNTEntity::~TNTEntity()
{
    //dtor
}

void TNTEntity::update(double delta)
{
    int demiSeconds = (int)(fuse.getElapsedTime().asSeconds() * 2);

    setFillColor((demiSeconds % 2) ? sf::Color(127, 127, 127) : sf::Color::White);
    setOnMapColor((demiSeconds % 2) ? sf::Color::Black : sf::Color::Red);

    if (!mustBeRemoved && fuse.getElapsedTime().asSeconds() >= 3.0f)
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
                        EventManager::OnBlockBreak(BlockBreakEvent(sf::Vector2u(xpos + x, ypos + y), oldBlockId, this, currentWorld->getStateGame()));
                    }
                    if (x * x + y * y <= 4) {
                        unsigned short oldGroundId = currentWorld->getGroundId(sf::Vector2u(xpos + x, ypos + y));
                        currentWorld->setGroundId(sf::Vector2u(xpos + x, ypos + y), 4);
                        EventManager::OnGroundPlace(GroundPlaceEvent(sf::Vector2u(xpos + x, ypos + y), oldGroundId, 4, this, currentWorld->getStateGame()));
                    }
                }
            }
        }
        mustBeRemoved = true;
    }
}

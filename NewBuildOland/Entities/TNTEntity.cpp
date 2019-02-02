#include "TNTEntity.h"
#include "../Events/EventManager.h"

TNTEntity::TNTEntity(World* world, unsigned id, sf::Vector2i pos) :
    Entities(world, id),
    fuseLenght(3.0f)
{
    setDataSize(2 * sizeof(int) + sizeof(float));

    worldPos = pos;
    fuse.restart();
    setSize(sf::Vector2f(80, 120));
    setTexture(game->getAssetManager()->getTexture("TNT"));
    setPosition(sf::Vector2f(pos.x * StateGame::TILE_SIZE, pos.y * StateGame::TILE_SIZE));
    setOrigin(sf::Vector2f(40, 80));
    setOnMapColor(sf::Color::Red);
}

TNTEntity::~TNTEntity()
{
    //dtor
}

void TNTEntity::update(float delta)
{
    int demiSeconds = (int)(fuse.getElapsedTime().asSeconds() * 2);

    setFillColor((demiSeconds % 2) ? sf::Color(127, 127, 127) : sf::Color::White);
    setOnMapColor((demiSeconds % 2) ? sf::Color::Black : sf::Color::Red);

    if (!game->isOnlineAndAvailible())
    {
        if (!mustBeRemoved && fuse.getElapsedTime().asSeconds() >= fuseLenght)
        {
            explode(worldPos);
        }
    }
}

void TNTEntity::takePacket(sf::Packet p)
{
    int x, y;
    float f;
    p >> x >> y >> f;
    worldPos = sf::Vector2i(x, y);
    setPosition(sf::Vector2f(x * StateGame::TILE_SIZE, y * StateGame::TILE_SIZE));
    fuseLenght = f;
    fuse.restart();
}

void TNTEntity::explode(sf::Vector2i center)
{
    sf::Sound* boomSound = new sf::Sound();
    game->getAssetManager()->addPlayingSound(boomSound);
    boomSound->setBuffer(*game->getAssetManager()->getSound("EXPLOSION"));
    boomSound->setVolume(20);
    boomSound->play();
    int xpos = center.x;
    int ypos = center.y;
    for (int x = -2; x <= 2; x++)
    {
        for (int y = -2; y <= 2; y++)
        {
            if (x * x + y * y <= 6)
            {
                unsigned short oldBlockId = currentWorld->getBlockId(sf::Vector2i(xpos + x, ypos + y));
                currentWorld->setBlockId(sf::Vector2i(xpos + x, ypos + y), 0);
                EventManager::OnBlockBreak(BlockBreakEvent(sf::Vector2i(xpos + x, ypos + y), oldBlockId, this, game));
            }
            if (x * x + y * y <= 4) {
                unsigned short oldGroundId = currentWorld->getGroundId(sf::Vector2i(xpos + x, ypos + y));
                currentWorld->setGroundId(sf::Vector2i(xpos + x, ypos + y), 4);
                EventManager::OnGroundPlace(GroundPlaceEvent(sf::Vector2i(xpos + x, ypos + y), oldGroundId, 4, this, game));
            }
        }
    }
    mustBeRemoved = true;
}

#include "Player.h"
#include "../States/StateGame.h"
#include "../Utils/Animation.h"
#include "../Events/EventManager.h"
#include "../Events/PlaceableEnterEvent.h"
#include "../Events/PlaceableLeaveEvent.h"
#include <math.h>

Player::Player(World *world, sf::String displayName, unsigned int id)
	: LivingEntity(world, id, 20, 9) //Player's id client side is always 0, because it doesn't matter
{
	initInventory(currentWorld);

	font.loadFromFile("Res/font/lucon.ttf");
	nameText.setFont(font);
	nameText.setString(displayName);
	nameText.setOutlineColor(sf::Color(0, 0, 0, 127));
	nameText.setOutlineThickness(2);
	nameText.setCharacterSize(25);
}

void Player::initInventory(World* currentWorld) {
    Inventory *inventory = getInventory();
    //Later : save / load inventory from file
    TileSet* tileset = currentWorld->getStateGame()->getTileset();
    inventory->addItem(ItemStack(tileset->getBlockById(1), 100));
    inventory->addItem(ItemStack(tileset->getBlockById(2), 100));
    inventory->addItem(ItemStack(tileset->getBlockById(7), 100));
    inventory->addItem(ItemStack(tileset->getBlockById(4), 100));
    inventory->addItem(ItemStack(tileset->getBlockById(5), 100));
    inventory->addItem(ItemStack(tileset->getBlockById(6), 100));
    inventory->addItem(ItemStack(tileset->getGroundById(0), 120));
    inventory->addItem(ItemStack(tileset->getGroundById(1), 120));
}

void Player::updateMovement(double dt) {
    //HANDLE INPUT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        moveWest(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        moveEast(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        moveNorth(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        moveSouth(dt);
    }

    //Block enter and leave event
    sf::Vector2i blockOn = sf::Vector2i(roundf(getPosition().x / StateGame::TILE_SIZE), roundf(getPosition().y / StateGame::TILE_SIZE));
    sf::Vector2u uBlockOn = sf::Vector2u(blockOn.x, blockOn.y);
    if (lastPos != uBlockOn)
    {
        unsigned short blockId = currentWorld->getBlockId(blockOn.x, blockOn.y);
        unsigned short groundId = currentWorld->getGroundId(blockOn.x, blockOn.y);
        EventManager::OnPlaceableLeave(PlaceableLeaveEvent(lastPos, this, blockId, groundId, currentWorld->getStateGame()));
        if (blockOn.x >= 0 && blockOn.y >= 0 && blockOn.x < currentWorld->getWorldSize().x && blockOn.y < currentWorld->getWorldSize().y)
            EventManager::OnPlaceableEnter(PlaceableEnterEvent(lastPos, this, blockId, groundId, currentWorld->getStateGame()));
        lastPos = uBlockOn;
    }
}

std::string Player::getTextureName() {
    return "characters.png";
}
std::vector<IntRect> Player::getIdleAnim() {
    std::vector<sf::IntRect> idleAnim = std::vector<sf::IntRect>();
    idleAnim.push_back(sf::IntRect(37, 9, 32, 32));

    return idleAnim;
}
std::vector<IntRect> Player::getNorthWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim.push_back(sf::IntRect(5, 105, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 105, 32, 32));
    walkingAnim.push_back(sf::IntRect(69, 105, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 105, 32, 32));

    return walkingAnim;
}
std::vector<IntRect> Player::getSouthWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim = std::vector<sf::IntRect>();
    walkingAnim.push_back(sf::IntRect(5, 9, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 9, 32, 32));
    walkingAnim.push_back(sf::IntRect(69, 9, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 9, 32, 32));

    return walkingAnim;
}
std::vector<IntRect> Player::getEastWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim = std::vector<sf::IntRect>();
    walkingAnim.push_back(sf::IntRect(5, 73, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 73, 32, 32));
    walkingAnim.push_back(sf::IntRect(69, 73, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 73, 32, 32));

    return walkingAnim;
}
std::vector<IntRect> Player::getWestWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim.push_back(sf::IntRect(5, 41, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 41, 32, 32));
    walkingAnim.push_back(sf::IntRect(69, 41, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 41, 32, 32));

    return walkingAnim;
}


Player::~Player()
{
}

void Player::drawMore(sf::RenderWindow& window)
{
    nameText.setPosition(getPosition() - sf::Vector2f(nameText.getGlobalBounds().width / 2.f, getSize().y));
    window.draw(nameText);
}


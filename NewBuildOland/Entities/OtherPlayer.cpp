#include "OtherPlayer.h"
#include "../States/StateGame.h"
#include "../Utils/Animation.h"
#include "../Events/EventManager.h"
#include "../Events/PlaceableEnterEvent.h"
#include "../Events/PlaceableLeaveEvent.h"
#include <math.h>

OtherPlayer::OtherPlayer(World *world, sf::String displayName, unsigned id)
    : LivingEntity(world, id, 20, 9)
{
	nameText.setFont(*GameGlobal::assets.getFont("LUCON"));
	nameText.setString(displayName);
	nameText.setOutlineColor(sf::Color(0, 0, 0, 127));
	nameText.setOutlineThickness(2);
	nameText.setCharacterSize(25);
	setFillColor(sf::Color(255, 255, 200));

	movement = 0;
}

OtherPlayer::~OtherPlayer()
{
    //dtor
}

void OtherPlayer::takePacket(sf::Packet p)
{
    p >> movement;
    float x, y;
    p >> x >> y;
    setPosition(x, y);
}

void OtherPlayer::updateMovement(float dt)
{
    if (movement & 0b0001)
    {
        moveWest(dt);
    }
    if (movement & 0b0010)
    {
        moveEast(dt);
    }
    if (movement & 0b0100)
    {
        moveNorth(dt);
    }
    if (movement & 0b1000)
    {
        moveSouth(dt);
    }
}

std::string OtherPlayer::getTextureName() {
    return "CHARACTERS_SHEET_1";
}
std::vector<sf::IntRect> OtherPlayer::getIdleAnim() {
    std::vector<sf::IntRect> idleAnim = std::vector<sf::IntRect>();
    idleAnim.push_back(sf::IntRect(151, 9, 32, 32));

    return idleAnim;
}
std::vector<sf::IntRect> OtherPlayer::getNorthWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim.push_back(sf::IntRect(119, 105, 32, 32));
    walkingAnim.push_back(sf::IntRect(151, 105, 32, 32));
    walkingAnim.push_back(sf::IntRect(183, 105, 32, 32));
    walkingAnim.push_back(sf::IntRect(151, 105, 32, 32));

    return walkingAnim;
}
std::vector<sf::IntRect> OtherPlayer::getSouthWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim = std::vector<sf::IntRect>();
    walkingAnim.push_back(sf::IntRect(119, 9, 32, 32));
    walkingAnim.push_back(sf::IntRect(151, 9, 32, 32));
    walkingAnim.push_back(sf::IntRect(183, 9, 32, 32));
    walkingAnim.push_back(sf::IntRect(151, 9, 32, 32));

    return walkingAnim;
}
std::vector<sf::IntRect> OtherPlayer::getEastWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim = std::vector<sf::IntRect>();
    walkingAnim.push_back(sf::IntRect(119, 73, 32, 32));
    walkingAnim.push_back(sf::IntRect(151, 73, 32, 32));
    walkingAnim.push_back(sf::IntRect(183, 73, 32, 32));
    walkingAnim.push_back(sf::IntRect(151, 73, 32, 32));

    return walkingAnim;
}
std::vector<sf::IntRect> OtherPlayer::getWestWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim.push_back(sf::IntRect(119, 41, 32, 32));
    walkingAnim.push_back(sf::IntRect(151, 41, 32, 32));
    walkingAnim.push_back(sf::IntRect(183, 41, 32, 32));
    walkingAnim.push_back(sf::IntRect(151, 41, 32, 32));

    return walkingAnim;
}

void OtherPlayer::drawMore(sf::RenderWindow& window)
{
    nameText.setPosition(getPosition() - sf::Vector2f(nameText.getGlobalBounds().width / 2.f, getSize().y));
    window.draw(nameText);
}


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
    font.loadFromFile("Res/font/lucon.ttf");
	nameText.setFont(font);
	nameText.setString(displayName);
	nameText.setOutlineColor(sf::Color(0, 0, 0, 127));
	nameText.setOutlineThickness(2);
	nameText.setCharacterSize(25);
	setFillColor(sf::Color(255, 255, 200));
}

OtherPlayer::~OtherPlayer()
{
    //dtor
}

void OtherPlayer::updateMovement(double dt)
{

}

std::string OtherPlayer::getTextureName() {
    return "characters.png";
}
std::vector<IntRect> OtherPlayer::getIdleAnim() {
    std::vector<sf::IntRect> idleAnim = std::vector<sf::IntRect>();
    idleAnim.push_back(sf::IntRect(37, 9, 32, 32));

    return idleAnim;
}
std::vector<IntRect> OtherPlayer::getNorthWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim.push_back(sf::IntRect(5, 105, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 105, 32, 32));
    walkingAnim.push_back(sf::IntRect(69, 105, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 105, 32, 32));

    return walkingAnim;
}
std::vector<IntRect> OtherPlayer::getSouthWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim = std::vector<sf::IntRect>();
    walkingAnim.push_back(sf::IntRect(5, 9, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 9, 32, 32));
    walkingAnim.push_back(sf::IntRect(69, 9, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 9, 32, 32));

    return walkingAnim;
}
std::vector<IntRect> OtherPlayer::getEastWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim = std::vector<sf::IntRect>();
    walkingAnim.push_back(sf::IntRect(5, 73, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 73, 32, 32));
    walkingAnim.push_back(sf::IntRect(69, 73, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 73, 32, 32));

    return walkingAnim;
}
std::vector<IntRect> OtherPlayer::getWestWalkAnim() {
    std::vector<sf::IntRect> walkingAnim = std::vector<sf::IntRect>();

    walkingAnim.push_back(sf::IntRect(5, 41, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 41, 32, 32));
    walkingAnim.push_back(sf::IntRect(69, 41, 32, 32));
    walkingAnim.push_back(sf::IntRect(37, 41, 32, 32));

    return walkingAnim;
}

void OtherPlayer::drawMore(sf::RenderWindow& window)
{
    nameText.setPosition(getPosition() - sf::Vector2f(nameText.getGlobalBounds().width / 2.f, getSize().y));
    window.draw(nameText);
}


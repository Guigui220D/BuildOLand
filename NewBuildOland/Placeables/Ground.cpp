#include "Ground.h"
#include "../Events/PlaceableEnterEvent.h"
#include "../Events/PlaceableLeaveEvent.h"

Ground::Ground(sf::IntRect textureRect, std::string name, sf::Color mapColor) : Placeable(textureRect, name, mapColor)
{
}

Ground::~Ground()
{
}

bool Ground::isGround() {
    return true;
}

void Ground::OnPlaceableEnter(PlaceableEnterEvent e) {

}

void Ground::OnPlaceableLeave(PlaceableLeaveEvent e) {

}

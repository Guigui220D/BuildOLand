#include "GroundGrass.h"
#include "../Events/PlaceableEnterEvent.h"

GroundGrass::GroundGrass(sf::IntRect textureRect)
    : Ground(textureRect, "GRASS", sf::Color(135, 170, 55))
{
}

void GroundGrass::onPlaceableEnter(PlaceableEnterEvent e) {

}

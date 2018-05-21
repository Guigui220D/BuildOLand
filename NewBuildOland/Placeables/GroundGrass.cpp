#include "GroundGrass.h"
#include "../Events/PlaceableEnterEvent.h"

GroundGrass::GroundGrass(sf::IntRect textureRect)
    : Ground(textureRect, "GRASS", sf::Color(135, 170, 55))
{

}

void GroundGrass::onPlaceableEnter(PlaceableEnterEvent e) {
    sf::Sound* saveSound = e.getState()->getSoundManager()->getSound("grass1.ogg");

    saveSound->setVolume(70);
    saveSound->play();
}
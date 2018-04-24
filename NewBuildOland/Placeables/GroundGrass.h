
#pragma once


#include "Ground.h"
#include "../Events/PlaceableEnterEvent.h"

class GroundGrass : public Ground {
public:
    GroundGrass(sf::IntRect textureRect);

    void OnPlaceableEnter(PlaceableEnterEvent e) override;

};


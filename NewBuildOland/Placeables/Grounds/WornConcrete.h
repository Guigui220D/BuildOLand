#pragma once

#include "../Ground.h"

class WornConcrete : public Ground {
public:
    WornConcrete(sf::IntRect textureRect, std::string name, sf::Color mapColor);

    Ground *getGroundOnBreak(StateGame *stateGame) override;


};




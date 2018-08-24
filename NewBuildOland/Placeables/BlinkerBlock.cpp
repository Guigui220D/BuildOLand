#include "BlinkerBlock.h"

BlinkerBlock::BlinkerBlock(sf::IntRect textureRect, sf::IntRect faceRect) : Block(textureRect, "BLINKER", sf::Color(127, 127, 255), true, true, faceRect)
{
    //ctor
}

BlinkerBlock::~BlinkerBlock()
{
    //dtor
}

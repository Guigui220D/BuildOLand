#include "FpsCounter.h"
#include "../States/StateGame.h"
#include <iostream>
#include <sstream>
#include <cmath>

FpsCounter::FpsCounter(StateBase* stateBase) : Gui(stateBase)
{
    text.setFont(*GameGlobal::assets.getFont("LUCON"));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(32);
}

FpsCounter::~FpsCounter()
{}

void FpsCounter::draw(sf::RenderWindow &window)
{
    window.draw(text);
}

float FpsCounter::getFPS()
{
    return round(stateBase->getGame()->getFPS());
}

void FpsCounter::update(float dt) {
    std::stringstream s;
    s << "FPS : " << getFPS();
    text.setString(s.str());

}

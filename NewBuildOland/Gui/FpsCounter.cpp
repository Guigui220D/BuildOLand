#include "FpsCounter.h"
#include "../States/StateGame.h"
#include <iostream>
#include <sstream>
#include <cmath>

FpsCounter::FpsCounter(StateGame* stateGame) : Gui(stateGame)
{
    font.loadFromFile("Res/Font/lucon.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(32);
    text.setPosition(-stateGame->getGuiView().getSize().x / 2, -stateGame->getGuiView().getSize().y / 2);
}

FpsCounter::~FpsCounter()
{}

void FpsCounter::draw(sf::RenderWindow &window)
{
    window.draw(text);
}

double FpsCounter::getFPS()
{
    return round(stateGame->getGame()->getFPS());
}

void FpsCounter::update(float dt)
{
    std::stringstream s;
    s << "FPS : " << getFPS();
    text.setString(s.str());
}

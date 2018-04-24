#include "FpsCounter.h"
#include "../States/StateGame.h"
#include <iostream>
#include <sstream>
#include <cmath>

FpsCounter::FpsCounter(StateGame* game) : Gui(game)
{
    setSize(sf::Vector2f(0.27f, 0.05f));
    setPosition(sf::Vector2f(0.01f, 0.01f));
    setFillColor(sf::Color::Transparent);
    font.loadFromFile("Res/Font/lucon.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(16);
    text.setScale(sf::Vector2f(0.002f, 0.002f));
    text.setPosition(sf::Vector2f(0.02, 0.02));
}

FpsCounter::~FpsCounter()
{
    //dtor
}

void FpsCounter::drawMore(sf::RenderWindow &window)
{
    window.draw(text);
}

double FpsCounter::getFPS()
{
    return round(stateGame->getGame()->getFPS());
}

void FpsCounter::act()
{
    std::stringstream s;
    s << "FPS : " << getFPS();
    text.setString(s.str());
}

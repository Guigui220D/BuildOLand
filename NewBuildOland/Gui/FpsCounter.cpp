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
    f.loadFromFile("Res/Font/lucon.ttf");
    t.setFont(f);
    t.setFillColor(sf::Color::Black);
    t.setCharacterSize(16);
    t.setString("HEEEY");
    t.setScale(sf::Vector2f(0.002f, 0.002f));
    t.setPosition(sf::Vector2f(0.02, 0.02));
}

FpsCounter::~FpsCounter()
{
    //dtor
}

void FpsCounter::drawMore(sf::RenderWindow &window)
{
    window.draw(t);
}

double FpsCounter::getFPS()
{
    return round(stateGame->getGame()->getFPS());
}

void FpsCounter::act()
{
    std::stringstream s;
    s << "FPS : " << getFPS();
    t.setString(s.str());
}

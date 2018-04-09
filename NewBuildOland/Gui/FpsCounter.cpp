#include "FpsCounter.h"
#include "../States/StateGame.h"
#include <iostream>

FpsCounter::FpsCounter(StateGame* game) : Gui(game)
{
    setSize(sf::Vector2f(0.1f, 0.1f));
    setPosition(sf::Vector2f(0.01f, 0.01f));
    setFillColor(sf::Color::White);
}

FpsCounter::~FpsCounter()
{
    //dtor
}

void FpsCounter::drawMore(sf::RenderWindow &window)
{

}

double FpsCounter::getFPS()
{
    return stateGame->getGame()->getFPS();
}

void FpsCounter::act()
{
    std::cout << getFPS() << std::endl;
}

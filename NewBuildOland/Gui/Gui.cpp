#include "Gui.h"
#include <iostream>

Gui::Gui(StateGame* game)
{
    stateGame = game;
}

Gui::~Gui()
{
    //dtor
}

void Gui::drawMore(sf::RenderWindow &window)
{

}

void Gui::act()
{

}

void Gui::tellIExist()
{
    std::cout << "I exist" << std::endl;
}

#include "Gui.h"
#include <iostream>

Gui::Gui(StateGame* stateGame) : stateGame(stateGame)
{
}

Gui::~Gui()
{
}

bool Gui::handleEvent(sf::Event e)
{
    return false;
}

bool Gui::isReleased(sf::Vector2i mousePos) {
    return false;
}

bool Gui::isActive(sf::Vector2i mousePos) {
    return false;
}

bool Gui::isHovered(sf::Vector2i mousePos) {
    return false;
}

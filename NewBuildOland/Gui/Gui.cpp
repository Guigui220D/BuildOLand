#include "Gui.h"
#include <iostream>

Gui::Gui(StateBase* stateBase) :
    stateBase(stateBase)
{
}

Gui::~Gui()
{
}

bool Gui::handleEvent(sf::Event e)
{
    return false;
}

#include <iostream>
#include "GuiButton.h"
#include "../Game.h"
#include "../States/StateMenu.h"

GuiButton::GuiButton(StateBase* stateBase, std::string textString, sf::Vector2f pos) :
        Gui(stateBase),
        pos(pos)
{
    //TEXT
    text.setFont(*stateBase->getAssetManager()->getFont("LUCON"));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(40);
    text.setScale(sf::Vector2f(.3f, .3f));
    text.setString(textString);
    text.setPosition(pos.x + 5.f, pos.y + 2.5f);

    //BACKGROUND
    background = sf::RectangleShape();
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(100.f, 20.f));
    background.setPosition(pos.x, pos.y);
}

void GuiButton::update(float dt)
{
    sf::Vector2f mousePos = stateBase->getGame()->getWindow().mapPixelToCoords(sf::Mouse::getPosition(stateBase->getGame()->getWindow()));
    hovered = background.getGlobalBounds().contains(mousePos);
}

void GuiButton::draw(sf::RenderWindow &window)
{

    //Draw the background shadow
    sf::Vector2f backgroundPos = background.getPosition();
    background.setFillColor(sf::Color(0, 0, 0, 100));
    background.setPosition(backgroundPos.x + (hovered ? 5.f : 3.f), backgroundPos.y + (hovered ? 5.f : 3.f));
    window.draw(background);
    //And the background
    background.setFillColor(hovered ? sf::Color(255, 240, 220, 255) : sf::Color(255, 255, 255, 255));
    background.setPosition(backgroundPos.x, backgroundPos.y);
    window.draw(background);


    window.draw(text);
}

bool GuiButton::handleEvent(sf::Event e)
{
    if (e.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos = stateBase->getGame()->getWindow().mapPixelToCoords(sf::Mouse::getPosition(stateBase->getGame()->getWindow()));
        clickDowned = background.getGlobalBounds().contains(mousePos);
        if (clickDowned)
            return true;
    }
    if (e.type == sf::Event::MouseButtonReleased)
    {
        sf::Vector2f mousePos = stateBase->getGame()->getWindow().mapPixelToCoords(sf::Mouse::getPosition(stateBase->getGame()->getWindow()));
        if (clickDowned)
        {
            if (background.getGlobalBounds().contains(mousePos))
            {
                clicked = true;
                return true;
            }
            clickDowned = false;
        }
    }
    return false;
}

bool GuiButton::onClick()
{
    if (!clicked)
        return false;
    clicked = false;
    return true;
}

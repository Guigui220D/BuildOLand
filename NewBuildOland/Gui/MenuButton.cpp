#include <iostream>
#include "MenuButton.h"
#include "../Game.h"
#include "../States/StateMenu.h"

MenuButton::MenuButton(StateMenu* stateMenu, std::string textString, sf::Vector2f pos)
        : Gui(nullptr)
        , stateMenu(stateMenu)
        , pos(pos)
{
    //TEXT
    text.setFont(*stateMenu->getAssetManager()->getFont("LUCON"));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(45);
    text.setString(textString);
    text.setPosition(pos.x - text.getLocalBounds().width / 2,
                     pos.y - text.getLocalBounds().height / 2);

    //BACKGROUND
    background = sf::RectangleShape();
    background.setFillColor(sf::Color::White);
    background.setSize(sf::Vector2f(500, 100));
    background.setPosition(pos.x - background.getSize().x / 2,
                           pos.y - background.getSize().y / 2 + 13);
}

void MenuButton::update(float dt) {

}

void MenuButton::draw(sf::RenderWindow &window) {

    //Draw the background shadow
    sf::Vector2f backgroundPos = background.getPosition();
    background.setFillColor(sf::Color(0, 0, 0, 100));
    if(hovered) {
        background.setPosition(backgroundPos.x + 10, backgroundPos.y + 10);
    } else {
        background.setPosition(backgroundPos.x + 5, backgroundPos.y + 5);
    }
    window.draw(background);
    //And the background
    if(active) {
        background.setFillColor(sf::Color(200, 200, 200, 255));
    } else if(hovered) {
        background.setFillColor(sf::Color(230, 230, 230, 255));
    } else {
        background.setFillColor(sf::Color(255, 255, 255, 255));
    }
    background.setPosition(backgroundPos.x, backgroundPos.y);
    window.draw(background);


    window.draw(text);
}

bool MenuButton::isReleased(sf::Vector2i mousePos) {
    sf::Vector2f pixelPos = stateMenu->getGame()->getWindow().mapPixelToCoords(mousePos);

    released = pixelPos.x > background.getPosition().x &&
              pixelPos.x < background.getPosition().x + background.getSize().x &&
              pixelPos.y > background.getPosition().y &&
              pixelPos.y < background.getPosition().y + background.getSize().y &&
              !justGotResized;
    if(justGotResized) {
        justGotResized = false;
    }
    return released;
}

bool MenuButton::isActive(sf::Vector2i mousePos) {
    sf::Vector2f pixelPos = stateMenu->getGame()->getWindow().mapPixelToCoords(mousePos);

    active = pixelPos.x > background.getPosition().x &&
              pixelPos.x < background.getPosition().x + background.getSize().x &&
              pixelPos.y > background.getPosition().y &&
              pixelPos.y < background.getPosition().y + background.getSize().y;

    return active;

}

bool MenuButton::isHovered(sf::Vector2i mousePos) {
    sf::Vector2f pixelPos = stateMenu->getGame()->getWindow().mapPixelToCoords(mousePos);

    hovered = pixelPos.x > background.getPosition().x &&
              pixelPos.x < background.getPosition().x + background.getSize().x &&
              pixelPos.y > background.getPosition().y &&
              pixelPos.y < background.getPosition().y + background.getSize().y;

    //Stop being active if you don't hover the element
    if(active && !hovered) {
        active = false;
    }
    return hovered;
}

void MenuButton::eventResize() {
    justGotResized = true;
}

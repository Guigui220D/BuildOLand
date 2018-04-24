#include <sstream>
#include "InventoryGui.h"

InventoryGui::InventoryGui(StateGame *game, Inventory *inventory, unsigned short *cursorId)
    : Gui(game)
    , inventory(inventory)
    , cursorId(cursorId)
{

    setSize(sf::Vector2f(0.27f, 0.05f));
    setPosition(sf::Vector2f(0.01f, 0.01f));
    setFillColor(sf::Color::Transparent);

    font.loadFromFile("Res/Font/lucon.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(16);
    text.setString("Inventory");
    text.setScale(sf::Vector2f(0.002f, 0.002f));
    text.setPosition(sf::Vector2f(0.3, 0.02));
}

void InventoryGui::drawMore(sf::RenderWindow &window) {
    window.draw(text);
}

void InventoryGui::act() {
    std::stringstream s;
    s << inventory->getItem(*cursorId)->getItem()->getName() << " | " << inventory->getItem(*cursorId)->getQuantity();
    text.setString(s.str());
}

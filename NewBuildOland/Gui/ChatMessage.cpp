#include "ChatMessage.h"

ChatMessage::ChatMessage(std::string msg, ChatColor color) :
    content(msg),
    color(color)
{ }

sf::Text ChatMessage::getSfText()
{
    sf::Text t;
    t.setString(content);
    t.setOutlineColor(sf::Color::Black);
    t.setOutlineThickness(2.f);
    t.setFillColor(sf::Color((int)color));
    return t;
}

#pragma once
#include <string>
#include "../Utils/ChatColors.h"
#include <SFML/Graphics.hpp>

struct ChatMessage
{
    ChatMessage(std::string msg, ChatColor color = ChatColor::ChatWhite);

    std::string content;
    ChatColor color;

    sf::Text getSfText();
};

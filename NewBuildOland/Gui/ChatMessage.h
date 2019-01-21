#pragma once
#include <string>
#include "../Utils/ChatColors.h"

struct ChatMessage
{
    ChatMessage(std::string msg, ChatColor color = ChatColor::ChatWhite);

    std::string content;
    ChatColor color;
};

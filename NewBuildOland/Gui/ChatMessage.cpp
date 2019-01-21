#include "ChatMessage.h"
#include "../GameGlobal.h"

ChatMessage::ChatMessage(std::string msg, ChatColor color) :
    content(msg),
    color(color)
{ }

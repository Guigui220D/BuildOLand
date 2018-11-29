#include "Item.h"

Item::Item(const std::string name) : name(name) {

}

sf::IntRect Item::getItemTextureRect() const
{
    return sf::IntRect();
}

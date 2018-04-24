#include "Item.h"

Item::Item(const std::string name) : name(name) {

}

std::string Item::getName()
{
    return name;
}

#pragma once

#include <unordered_map>
#include <vector>

#include "../Placeables/Item.h"

class ItemSet
{
    public:
        ItemSet();
        virtual ~ItemSet();

        bool iterateThroughItems(Item*& item);

        inline Item* getItemById(unsigned int id) const
            { return items.at(id); }
        unsigned short getItemIdByName(const std::string name) const;
        inline Item* getItemByName(std::string name) const
            { return items.at(getItemIdByName(name)); }

        inline unsigned int getItemCount() const { return items.size(); }

    private:
        std::vector<Item*> items;
        std::unordered_map<std::string, unsigned short> itemNames;

        unsigned int iterator = 0;
};

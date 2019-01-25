#pragma once

#include <unordered_map>
#include <vector>
#include <math.h>

#include "../Placeables/Item.h"

class ItemSet
{
    public:
        inline static Item* getSomeAir() { return air; };

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
        static Item* air;

        std::vector<Item*> items;
        std::unordered_map<std::string, unsigned short> itemNames;

        void generateItems();
        void addItem(Item* item);
        //Creates an IntRect where the texture is according to the nth texture of the tileset
        const unsigned int TILES_IN_ROW = 5;
        const unsigned int TILE_SIZE = 32;
        inline sf::IntRect tileRectById(unsigned int tilesetId) const
            { return sf::IntRect(tilesetId % TILES_IN_ROW * (TILE_SIZE + 2) + 1, (int)floorf(tilesetId / TILES_IN_ROW) * (TILE_SIZE + 2) + 1, TILE_SIZE, TILE_SIZE); }

        unsigned int iterator = 0;
};

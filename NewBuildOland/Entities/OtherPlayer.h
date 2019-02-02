#pragma once
//#include "Entities.h"
//#include "PhysicEntity.h"
//#include "../Utils/Animation.h"
//#include "../Utils/Inventory.h"
#include "LivingEntity.h"


class OtherPlayer : public LivingEntity
{
    public:
        OtherPlayer(World *world, sf::String displayName, unsigned id);
        ~OtherPlayer();

        inline EntityCodes getCode() const override { return EntityCodes::player; };

        void drawMore(sf::RenderWindow& window) override;
        inline void setCurrentWorld(World* newWorld) { currentWorld = newWorld; };
        inline sf::String getDisplayName() { return nameText.getString(); };

        void takePacket(sf::Packet p) override;

    protected:

        std::string getTextureName() override;
        std::vector<sf::IntRect> getIdleAnim() override;
        std::vector<sf::IntRect> getNorthWalkAnim() override;
        std::vector<sf::IntRect> getSouthWalkAnim() override;
        std::vector<sf::IntRect> getEastWalkAnim() override;
        std::vector<sf::IntRect> getWestWalkAnim() override;

        void updateMovement(float dt) override;

        sf::Text nameText; //Display name


    private:

        sf::Vector2u lastPos;

        unsigned char movement;
};



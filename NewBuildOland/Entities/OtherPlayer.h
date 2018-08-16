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

        void drawMore(sf::RenderWindow& window) override;
        inline void setCurrentWorld(World* newWorld) { currentWorld = newWorld; };
        inline sf::String getDisplayName() { return nameText.getString(); };

        virtual void takePacket(sf::Packet p) override;

        virtual OtherPlayer* clone() const { return new OtherPlayer(*this); };

    protected:

        std::string getTextureName() override;
        std::vector<IntRect> getIdleAnim() override;
        std::vector<IntRect> getNorthWalkAnim() override;
        std::vector<IntRect> getSouthWalkAnim() override;
        std::vector<IntRect> getEastWalkAnim() override;
        std::vector<IntRect> getWestWalkAnim() override;

        void updateMovement(double dt) override;

        sf::Text nameText; //Display name


    private:

        sf::Vector2u lastPos;
        sf::Font font;

        unsigned char movement;
};



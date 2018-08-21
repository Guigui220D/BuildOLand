#pragma once
#include "PhysicEntity.h"
#include "../Utils/Animation.h"
#include "../Utils/Inventory.h"

class LivingEntity : public PhysicEntity {
//Class that has animations, states, can move, can have an AI etc
//Has also an inventory, health

public:
    LivingEntity(World *world, unsigned id, unsigned short maxHealth, unsigned short inventorySize);

    void update(float dt) override;

    void init(float posX, float posY);

    Inventory* getInventory();

protected:
    //Texture methods
    virtual std::string getTextureName() = 0;
    virtual std::vector<sf::IntRect> getIdleAnim() = 0;
    virtual std::vector<sf::IntRect> getNorthWalkAnim() = 0;
    virtual std::vector<sf::IntRect> getSouthWalkAnim() = 0;
    virtual std::vector<sf::IntRect> getEastWalkAnim() = 0;
    virtual std::vector<sf::IntRect> getWestWalkAnim() = 0;
    virtual float animInterval();

    void moveNorth(float dt);
    void moveSouth(float dt);
    void moveEast(float dt);
    void moveWest(float dt);

    virtual void updateMovement(float dt) = 0;

protected:
    int EntitySpeed = 300;
private:
    void initAnimations();
    void selectAnimation();

    Animation animations;

    short health;
    Inventory inventory;

    //The movement byte is used as a flag to choose the right animation
    char movement;
};



